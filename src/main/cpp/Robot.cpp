// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>

Robot::Robot() {
  m_cam = std::make_shared<PhotonVisionCamera>("FRC_830-CAM", m_robotToCamera);
}  

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  auto data = m_cam->GetPose();
  double x = 0.0f;
  double y = 0.0f;

  if (data.has_value())
  {
    auto pose = data.value().estimatedPose;
    x = pose.X().value();
    y = pose.Y().value();
  }

  frc::SmartDashboard::PutNumber("Data.x", x);
  frc::SmartDashboard::PutNumber("Data.y", y);

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
