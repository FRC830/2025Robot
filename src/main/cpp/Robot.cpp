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
  
if(controller1.GetLeftY()>=0.1||controller1.GetLeftY()<=-0.1){
  if(controller1.GetLeftY()>=0){
    if(controller1.GetLeftBumper())
    {
       motor1.Set((controller1.GetLeftY()-0.1)*10.0/9.0*0.2);
    }
    else
    {
        motor1.Set((controller1.GetLeftY()-0.1)*10.0/9.0);
    }
  }
else{
  motor1.Set(0);
}


if(controller1.GetLeftY()<0){
 if(controller1.GetLeftBumper()){
  motor1.Set((controller1.GetLeftY()+0.1)*10.0/9.0*0.2);
 }
 else{
 motor1.Set((controller1.GetLeftY()+0.1)*10.0/9.0);
 }
}
else{
  motor1.Set(0);
}

}





if(controller1.GetLeftX()>=0.1||controller1.GetLeftX()<=-0.1){
if(controller1.GetLeftX()>=0){
 if(controller1.GetLeftBumper()){
  motor2.Set((controller1.GetLeftX()-0.1)*10.0/9.0*0.2);
 }
 else{
 motor2.Set((controller1.GetLeftX()-0.1)*10.0/9.0);
 }
}
if(controller1.GetLeftX()<0){
 if(controller1.GetLeftBumper()){
  motor2.Set((controller1.GetLeftX()+0.1)*10.0/9.0*0.2);
 }
 else{
 motor2.Set((controller1.GetLeftX()+0.1)*10.0/9.0);
 }
}
else{
  motor2.Set(0);
}

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