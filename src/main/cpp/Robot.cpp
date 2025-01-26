// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>

Robot::Robot() {
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
  _controller_interface.UpdateRobotControlData(_robot_control_data);

  if (_robot_control_data.swerveInput.rotation > GetSwerveDeadZone() || _robot_control_data.swerveInput.rotation < -GetSwerveDeadZone())
  {
    _robot_control_data.swerveInput.targetLeftFeederAngle = false;
    _robot_control_data.swerveInput.targetRightFeederAngle = false;
  }
  if(_robot_control_data.swerveInput.targetLeftFeederAngle)
  {
    auto chassisRotateToFeeder =  m_rotateToFeeder.move(_swerve.GetPose(), frc::Pose2d(0.0_m, 0.0_m, frc::Rotation2d(ROTATION_TO_FEEDER)));
    _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, chassisRotateToFeeder.omega);
  }
  else if(_robot_control_data.swerveInput.targetRightFeederAngle)
  {
    auto chassisRotateToFeeder =  m_rotateToFeeder.move(_swerve.GetPose(), frc::Pose2d(0.0_m, 0.0_m, frc::Rotation2d(-ROTATION_TO_FEEDER)));
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
