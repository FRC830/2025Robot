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
  if((m_conchroller.GetRightX() > 0.1) or (m_conchroller.GetRightX() < -0.1)){
    m_leftRight.Set(m_conchroller.GetRightX());
    } else{
      m_leftRight.Set(0);
    }
    
  if((m_conchroller.GetRightY() > 0.1) or (m_conchroller.GetRightY() < -0.1)){
    m_frontBack.Set(m_conchroller.GetRightY());
    } else{
      m_frontBack.Set(0);
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