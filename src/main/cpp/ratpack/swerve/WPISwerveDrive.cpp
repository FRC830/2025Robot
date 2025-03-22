#include "ratpack/swerve/WPISwerveDrive.h"
#include "frc/Timer.h"
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <math.h>
#include <frc/DriverStation.h>
#include <pathplanner/lib/config/RobotConfig.h>

void WPISwerveDrive::Configure(SwerveConfig &config){
    frc::SmartDashboard::PutData("Field", &m_field);
    m_ebrake = config.ebrake;
    m_maxDriveSpeed = config.maxDriveSpeed;
    m_maxTurnSpeed = config.maxTurnSpeed;
    m_orientation = config.orientation;
    m_frontLeftLocation = config.frontLeftLocation;
    m_frontRightLocation = config.frontRightLocation;
    m_backLeftLocation = config.backLeftLocation;
    m_backRightLocation = config.backRightLocation;
    SetIdleMode(config.idle_mode);
    //m_modules = config.modules;
    m_kinematics = new frc::SwerveDriveKinematics(m_frontLeftLocation, m_frontRightLocation, m_backLeftLocation, m_backRightLocation);
    m_deadzone = config.deadzone;
    m_gyro = config.gyro;
    //Last parameter in constuer must be relative the actual robot for it to wrok some what correctly
    //REMEMEBR TO FLIP DIRECTION DURING AUTON MAKING
    m_estimator = new frc::SwerveDrivePoseEstimator<4>(*m_kinematics, m_gyro->GetRawHeading(), {m_modules[0]->GetPosition(), m_modules[1]->GetPosition(), m_modules[2]->GetPosition(), m_modules[3]->GetPosition()}, frc::Pose2d(frc::Translation2d(), m_gyro->GetHeading()));

    pathplanner::RobotConfig pathplanner_config = pathplanner::RobotConfig::fromGUISettings();

    pathplanner::AutoBuilder::configure(
        [this]() {return GetPose();},
        [this](frc::Pose2d InitPose)  {ResetPose(InitPose);},
        [this](){return GetRobotRelativeSpeeds(); },
        [this](frc::ChassisSpeeds speeds) {Drive(speeds);},
        std::make_shared<pathplanner::PPHolonomicDriveController>( 
            pathplanner::PIDConstants(5.0, 0.0, 0.0), // Translation PID constants
            pathplanner::PIDConstants(5.0, 0.0, 0.0) // Rotation PID constants
        ),
        pathplanner_config,
        []() { return true;},
        {nullptr}
    );

}

bool WPISwerveDrive::GetEbrake() {
    return m_ebrake;
}
void WPISwerveDrive::SetEbrake(bool ebrake) {
    m_ebrake = ebrake;
}
void WPISwerveDrive::Drive(double x_position, double y_position, double rotation) {
    auto val = ApplyCylindricalDeadzone(x_position, y_position);
    x_position = val.first;
    y_position = val.second;
    rotation = ApplyDeadzone(rotation);

     Drive(
     (units::feet_per_second_t)x_position * m_maxDriveSpeed, 
     (units::feet_per_second_t)y_position * m_maxDriveSpeed, 
     (units::degrees_per_second_t)rotation * m_maxTurnSpeed);

}

void WPISwerveDrive::Drive(double x_position, double y_position, units::degrees_per_second_t omega) {
    auto val = ApplyCylindricalDeadzone(x_position, y_position);
    x_position = val.first;
    y_position = val.second;

    Drive(
     (units::feet_per_second_t)x_position * m_maxDriveSpeed, 
     (units::feet_per_second_t)y_position * m_maxDriveSpeed, 
     omega);
}
#include <iostream>
void WPISwerveDrive::Drive(units::feet_per_second_t vx, units::feet_per_second_t vy, units::degrees_per_second_t omega) {
    frc::SmartDashboard::PutNumber("Omega", static_cast<double>(omega));

    if (!m_orientation)
    {
        //std::cout << "robot" << std::endl;
        Drive(frc::ChassisSpeeds{vx, vy, omega});   
    }
    else
    {
        //std::cout << "field" << std::endl;
        frc::ChassisSpeeds speeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(vx, vy, omega, m_gyro->GetRawHeading());
        Drive(speeds);
    }
}   

void WPISwerveDrive::Drive(frc::ChassisSpeeds speed) {
    
    // states = m_kinematics.ToSwerveModuleStates(speed);
    auto states = m_kinematics->ToSwerveModuleStates(speed);
    
    m_kinematics->DesaturateWheelSpeeds(&states, units::feet_per_second_t(m_maxDriveSpeed));


    std::vector<frc::SwerveModuleState> stateN;
    stateN.push_back(states[0]);
    stateN.push_back(states[1]);
    stateN.push_back(states[2]);
    stateN.push_back(states[3]);

    Drive(stateN);

}
void WPISwerveDrive::Drive(std::vector<frc::SwerveModuleState> &state) {

    if (!m_ebrake)
    {
        if (m_shouldSwerveLock)
        {
            bool lockSwerveModules = true;
            for (int i = 0; i < state.size(); i++)
            {
                lockSwerveModules = lockSwerveModules && (std::fabs(double(state[i].speed) < 0.01));
            }

            if (lockSwerveModules)
            {
                state[0].angle = frc::Rotation2d(units::degree_t(315.0));
                state[1].angle = frc::Rotation2d(units::degree_t(45.0));
                state[2].angle = frc::Rotation2d(units::degree_t(45.0));
                state[3].angle = frc::Rotation2d(units::degree_t(315.0));
            }
        }

        for(int i = 0; i < state.size(); i++){
            m_modules[i]->SetState(state[i]);
        }
    }

    // frc::SmartDashboard::PutNumber("Degrees Of Gyro from RAW", m_gyro->GetRawHeading().Degrees().to<double>());

    // frc::SmartDashboard::PutNumber("Degrees Of Gyro from Processed", m_gyro->GetRawHeading().Degrees().to<double>());

    // frc::SmartDashboard::PutNumber("")

    // frc::SmartDashboard::PutData("Rotation2d", )
    

    m_estimator->UpdateWithTime(frc::Timer::GetFPGATimestamp(), m_gyro->GetRawHeading(), {m_modules[0]->GetPosition(), m_modules[1]->GetPosition(), m_modules[2]->GetPosition(), m_modules[3]->GetPosition()});
    m_field.SetRobotPose(m_estimator->GetEstimatedPosition());
} 

bool WPISwerveDrive::GetIdleMode() {
    return false;
}

void WPISwerveDrive::SetIdleMode(bool idle_mode) {
     for(int i = 0; i < m_modules.size(); i++){

        m_modules[i]->SetIdleMode(idle_mode);

    }
}
void WPISwerveDrive::SetRobotOriented() {
    m_orientation = false;
}
void WPISwerveDrive::SetFieldOriented() {
    m_orientation = true; 
}
bool WPISwerveDrive::GetOrientedMode() {
    return m_orientation;
}

frc::Pose2d WPISwerveDrive::GetPose()
{
    return m_estimator->GetEstimatedPosition();
}

void WPISwerveDrive::ResetPose(frc::Pose2d pose)
{
    m_estimator->ResetPosition(m_gyro->GetRawHeading(), {m_modules[0]->GetPosition(), m_modules[1]->GetPosition(), m_modules[2]->GetPosition(), m_modules[3]->GetPosition()}, pose);
}

frc::ChassisSpeeds WPISwerveDrive::GetRobotRelativeSpeeds()
{
    return m_kinematics->ToChassisSpeeds({m_modules[0]->GetState(), m_modules[1]->GetState(), m_modules[2]->GetState(), m_modules[3]->GetState()});
}

void WPISwerveDrive::UpdatePoseWithVision(frc::Pose3d pose3d, units::second_t timestamp)
{
    frc::Pose2d pose{frc::Translation2d{pose3d.X(), pose3d.Y()}, m_gyro->GetHeading()};
    if (!m_visionResetOccurred)
    {
        m_estimator->ResetPose(pose);
        m_visionResetOccurred = true;
    }
    else
    {
        m_estimator->AddVisionMeasurement(pose, timestamp);
    }
}

double WPISwerveDrive::ApplyDeadzone(double input)
{
    double output = 0;

    if (input > m_deadzone)
    {
        output = (input - m_deadzone) / (1 - m_deadzone);
    }
    else if (input < -(m_deadzone))
    {
        output = (input + m_deadzone) / (1 - m_deadzone);
    }

    return output;
}

std::pair<double, double> WPISwerveDrive::ApplyCylindricalDeadzone(double x, double y)
{
    double d =sqrt(pow(x,2)+pow(y,2));
    if((d)<= m_deadzone)
    {
        x=0.0;
        y=0.0;
    }
    else
    {
        double angle = atan2(y,x);
        double r = ((d-m_deadzone)/(1.0-m_deadzone));
        x = r*(cos(angle));
        y = r*(sin(angle));
    }

    return std::make_pair(x, y);
}

void WPISwerveDrive::SetShouldSwerveLock(bool shouldLock)
{
    m_shouldSwerveLock = shouldLock;
}