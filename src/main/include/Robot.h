// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <optional> 

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include <frc/Timer.h>
#include <frc/XboxController.h>
#include <rev/SparkMax.h>

class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void DisabledExit() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void AutonomousExit() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TeleopExit() override;
  void TestInit() override;
  void TestPeriodic() override;
  void TestExit() override;
  void SwerveInit();
  void PrintSwerveInfo();

 private:
  frc::XboxController exampleXbox{0}; // 0 is the USB Port to be used as indicated on the Driver Station
  rev::spark::SparkMax vehicleTranslator{61, rev::spark::SparkMax::MotorType::kBrushless};
  rev::spark::SparkMax vehicleTurner{60, rev::spark::SparkMax::MotorType::kBrushless};

  };
