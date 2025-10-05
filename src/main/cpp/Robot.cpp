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
  float a = 1;
  if(exampleXbox.GetBButton()) {
    a = 0.25;
  } 
  if(exampleXbox.GetLeftY() < -0.1 || exampleXbox.GetLeftY() > 0.1)
  {
    vehicleTranslator.Set(exampleXbox.GetLeftY() * a);
  }
  else
  {
    vehicleTranslator.Set(0);
  }
  if(exampleXbox.GetLeftX() < -0.1 || exampleXbox.GetLeftX() > 0.1)
  {
    vehicleTurner.Set(exampleXbox.GetLeftX() * a);
  }
  else
  {
    vehicleTurner.Set(0);
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