// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <optional> 

#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include <pathplanner/lib/commands/PathPlannerAuto.h>
#include "PhotonVisionCamera.h"

#include "ratpack/swerve/AnalogAbsoluteEncoder.h"
#include "ratpack/swerve/NavXGyro.h"
#include "ratpack/swerve/NeoDriveMotor.h"
#include "ratpack/swerve/NeoTurnMotor.h"
#include "ratpack/swerve/WPISwerveModule.h"
#include "ratpack/swerve/WPISwerveDrive.h"

  #include "InputManager/CoralLauncherManager.h"
#include "PhotonVisionCamera.h"

#include "ControllerInterface.h"
#include "RobotControlData.h"
#include "MoveToPose.h"

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
  double GetSwerveDeadZone();

  std::optional<frc2::CommandPtr> m_autonomousCommand;

  static const int NUM_MODULES = 4;

  std::array<AnalogAbsoluteEncoder, NUM_MODULES> _abs_encoders;
  std::array<NeoTurnMotor, NUM_MODULES> _turn_motors;
  std::array<NeoDriveMotor, NUM_MODULES> _drive_motors;
  std::array<WPISwerveModule, NUM_MODULES> _modules;
  WPISwerveDrive _swerve;

  NavXGyro _gyro;
  ControllerInterface _controller_interface;
  RobotControlData _robot_control_data;
  MoveToPose m_rotateToFeeder;

  frc::Rotation2d ROTATION_TO_FEEDER = frc::Rotation2d(units::degree_t{90.0});
  frc::Transform3d ROBOT_TO_CAMERA = frc::Transform3d(frc::Translation3d(5_m, 0_m, 0.5_m), frc::Rotation3d(0_rad, 0_rad, 0_rad));
  int m_state = 0;
  frc2::Command* m_auto;

  frc::SendableChooser<frc2::Command*> m_autoChooser;
  
  std::shared_ptr<PhotonVisionCamera> m_cam;
};
