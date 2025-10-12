// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc2/command/CommandScheduler.h>

bool slowmode = false;

Robot::Robot() {
}

void Robot::RobotPeriodic() {
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
  m_CoralLauncherManager.ResetState(m_ControlData);
}

void Robot::TeleopPeriodic() {
  m_ControllerInterface.UpdateRobotControlData(m_ControlData);
  if (!IsAutonomous()){
    m_CoralLauncherManager.HandleInput(m_ControlData);

}
}

void Robot::TeleopExit() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {

}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif