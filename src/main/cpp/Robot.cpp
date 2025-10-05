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
  float slowmode=1;
if (DaveBox.GetXButton()){
  slowmode=0.15;
}
if (DaveBox.GetRightX() >= 0.15 || DaveBox.GetRightX() <= -0.15) {
  CallumMotor.Set((slowmode * DaveBox.GetRightX()) -0.15);
} else {
  CallumMotor.Set(0);
}
if (DaveBox.GetRightY() >= 0.15 || DaveBox.GetRightY() <= -0.15) {
  SenithMotor.Set(slowmode * DaveBox.GetRightY() -0.15);
} else {
  SenithMotor.Set(0);
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
