// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>

#include "MechanismConfig.h"

Robot::Robot() {
  m_cam = std::make_shared<PhotonVisionCamera>("FRC_830-CAM", ratbot::VisionConfig::ROBOT_TO_CAMERA);
  SwerveInit();
}

void Robot::RobotPeriodic() {
  PrintSwerveInfo();
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {

  // m_cam->SaveResult();
  // frc::SmartDashboard::PutNumber("April Tag ID", m_cam->GetAprilTagID());
  // auto data = m_cam->GetPose();
  // double x = 0.0f;
  // double y = 0.0f;

  // if (data.has_value())
  // {
  //   auto pose = data.value().estimatedPose;
  //   x = pose.X().value();
  //   y = pose.Y().value();
  // }

  // frc::SmartDashboard::PutNumber("Data.x", x);
  // frc::SmartDashboard::PutNumber("Data.y", y);
  _controller_interface.UpdateRobotControlData(_robot_control_data);

  if (_robot_control_data.swerveInput.rotation > GetSwerveDeadZone() || _robot_control_data.swerveInput.rotation < -GetSwerveDeadZone())
  {
    _robot_control_data.swerveInput.targetLeftFeederAngle = false;
    _robot_control_data.swerveInput.targetRightFeederAngle = false;
  }
  if(_robot_control_data.swerveInput.targetLeftFeederAngle)
  {
    auto chassisRotateToFeeder =  m_rotateToFeeder.move(_swerve.GetPose(), frc::Pose2d(0.0_m, 0.0_m, frc::Rotation2d(ratbot::IntakeConfig::ROTATION_TO_FEEDER)));
    _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, chassisRotateToFeeder.omega);
  }
  else if(_robot_control_data.swerveInput.targetRightFeederAngle)
  {
    auto chassisRotateToFeeder =  m_rotateToFeeder.move(_swerve.GetPose(), frc::Pose2d(0.0_m, 0.0_m, frc::Rotation2d(-ratbot::IntakeConfig::ROTATION_TO_FEEDER)));
    _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, chassisRotateToFeeder.omega);
    
  }
  else
  {
    m_rotateToFeeder.reset();
    _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, _robot_control_data.swerveInput.rotation);
  }
}

void Robot::TeleopExit() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
