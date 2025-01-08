#include "MoveToPose.h"

// TODO: look at these files to understand how to setup and use a trapezoid move using switch statements
        // - https://github.com/FRC830/2024Robot/blob/master/src/main/include/subsystems/IntakeHAL.h (trapezoid move member variable init)
       //  - https://github.com/FRC830/2024Robot/blob/master/src/main/cpp/subsystems/IntakeHAL.cpp (ProfiledMoveToAngle function)
// TODO: don't worry about doing anything with the drive base for now

void MoveToPose::move(frc::Pose2d desired) {
    frc::Pose2d current;    
    switch(m_MoveToState){
        case 0:
        {
            // query swerve for current position when that function exists later
            current = frc::Pose2d{0_m, 0_m, frc::Rotation2d(0_deg)};
            m_MoveToState++;
            break;
        }
        case 1:
        {
            move(current, desired);
            m_MoveToState++;
            break;
        }
        default:
        {
            break;
        }
    }
    
};

void MoveToPose::move(frc::Pose2d current, frc::Pose2d desired) {
    angularRotation(current.Rotation(), desired.Rotation());
    linearTranslation(current, desired);  
};

void MoveToPose::angularRotation(frc::Rotation2d current, frc::Rotation2d desired) {
    switch (m_MoveAngleToState)
    {
        case 0:
        {
            m_timer.Restart();
            
            
            m_MoveAngleToState++;
            break;
        }
        case 1:
        {
            auto setPoint = m_Profile.Calculate(
                m_timer.Get(),
                frc::TrapezoidProfile<units::degrees>::State{current.Degrees(), 0_deg_per_s},
                frc::TrapezoidProfile<units::degrees>::State{desired.Degrees(), 0_deg_per_s}           
            );

            // todo rotate robot with setpoint when that function exists later

            if (m_Profile.IsFinished(m_timer.Get())) {
                m_MoveAngleToState++;
            }

            break;
        }
        case 2:
        {
            m_timer.Stop();
            m_MoveAngleToState++;
            break;
        }
        default:
        {
            break;
        }
    }
};

double MoveToPose::linearTranslation(frc::Pose2d current, frc::Pose2d desired) {
    // double distance = sqrt(pow((double)desired.X() - current.X(), 2.0) + pow(0.0 + desired.Y() - current.Y(), 2.0));
    double desiredx = desired.X().value();
    double currentx = current.X().value();
    double desiredy = desired.Y().value();
    double currenty = current.Y().value();

    
    
    double x = (desiredx - currentx) * (desiredx - currentx);
    double y = (desiredy - currenty) * (desiredy - currenty);
    
    double distance = sqrt(x + y);
    return distance;
};