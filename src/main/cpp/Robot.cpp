// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>

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

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  m_motor.Set(0.2*m_conchroller.GetRightY());
  m_minimotor.Set(0.5*m_conchroller.GetLeftY());
  if (m_conchroller.GetAButtonPressed()) {
    angle += 10.0;
    s_servo.SetAngle(angle);
  }
  if (m_conchroller.GetBButtonPressed()) {
    angle -= 10.0;
    s_servo.SetAngle(angle);
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