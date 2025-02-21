// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <iostream>

Robot::Robot() {
  SwerveInit();


  m_autos_directory = frc::filesystem::GetDeployDirectory();
  
   //"C:\workspace\2025Robot\vendordeps\deploy\pathplanner\autos"
  m_autos_directory = m_autos_directory / "pathplanner" / "autos";
  m_auto_chooser.SetDefaultOption("New Auto", "New Auto");

  int fileExtensionChar;

  for (auto i : std::filesystem::directory_iterator(m_autos_directory))
  {
    std::string filename = std::filesystem::path(i.path().string()).filename().string();
    fileExtensionChar = filename.rfind('.');

    if (fileExtensionChar != -1)
    {
      filename.erase(fileExtensionChar, 5);
      m_auto_chooser.AddOption(filename, filename);
    }
  }

  
  frc::SmartDashboard::PutData("Pathplanner Autos", &m_auto_chooser);

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
