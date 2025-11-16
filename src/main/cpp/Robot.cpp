// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <pathplanner/lib/auto/AutoBuilder.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include "MechanismConfig.h"
#include <pathplanner/lib/auto/NamedCommands.h>

#include "cmds/ShootCoral.h"
#include "cmds/LowerArm.h"
#include "cmds/RaiseArm.h"
#include "cmds/RaiseArmToBottom.h"
#include "cmds/UseSmartPlan.h"

Robot::Robot() {
  m_cam = std::make_shared<PhotonVisionCamera>("Climber cam", ratbot::VisionConfig::ROBOT_TO_CAMERA);
  
  pathplanner::NamedCommands::registerCommand("shoot", std::make_shared<ShootCoral>(_robot_control_data));
  pathplanner::NamedCommands::registerCommand("raise", std::make_shared<RaiseArm>(_robot_control_data));
  pathplanner::NamedCommands::registerCommand("lower", std::make_shared<LowerArm>(_robot_control_data));
  pathplanner::NamedCommands::registerCommand("raiseToBottom", std::make_shared<RaiseArmToBottom>(_robot_control_data));
  pathplanner::NamedCommands::registerCommand("smartplan", std::make_shared<UseSmartPlan>(_robot_control_data));

  SwerveInit();

  m_smartPlanner = std::make_shared<SmartPlanner>(*m_cam, _swerve);
  
  m_autoChooser = pathplanner::AutoBuilder::buildAutoChooser();
  frc::SmartDashboard::PutData("Auto Chooser", &m_autoChooser);

  _swerve.SetShouldSwerveLock(false);
}

void Robot::RobotPeriodic() {
  PrintSwerveInfo();
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {
  m_state = 0;
  m_auto = m_autoChooser.GetSelected();

  autonTimer.Stop();
  autonTimer.Reset();
  autonTimer.Start();
}

void Robot::AutonomousPeriodic() {

  switch(m_state)
  {
    case 0:
      {
        m_auto->Initialize();
        m_state++;
      }
      break;
    case 1:
      {
        m_auto->Execute();
        if (m_auto->IsFinished())
        {
          m_state++;
        }
      }
      break;
    case 2:
      {
        m_auto->End(false);
        m_state++;
      }
      break;
    case 3:
      {
        _swerve.Drive(0.0, 0.0, 0.0);
      }
    
      break;
    default:
      break;
  }

  TeleopPeriodic();

}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
  m_coralLauncherManager.ResetState();
  m_algaeRemoverManager.ResetState(_robot_control_data);
  m_ClimberManager.ResetState();


}

void Robot::TeleopPeriodic() {

  // Start normal teleop
  m_cam->SaveResult();

  if (!IsAutonomous())
  {
    _controller_interface.UpdateRobotControlData(_robot_control_data);
  }

  bool userWantsToSmartPlan = _robot_control_data.plannerInput.Left_L1
                            || _robot_control_data.plannerInput.Right_L1
                            || _robot_control_data.plannerInput.Left_L2
                            || _robot_control_data.plannerInput.Right_L2;

  m_smartPlanner->HandleInput(_robot_control_data);
  if (!userWantsToSmartPlan && !IsAutonomous())
  {
      if (_robot_control_data.swerveInput.rotation > GetSwerveDeadZone() || _robot_control_data.swerveInput.rotation < -GetSwerveDeadZone())
      {
        _robot_control_data.swerveInput.targetLeftFeederAngle = false;
        _robot_control_data.swerveInput.targetRightFeederAngle = false;
      }
      if(_robot_control_data.swerveInput.targetLeftFeederAngle)
      {
        auto chassisRotateToFeeder =  m_rotateToFeeder.move(_swerve.GetPose(), frc::Pose2d(0.0_m, 0.0_m, frc::Rotation2d(-ratbot::IntakeConfig::ROTATION_TO_FEEDER)));
        _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, chassisRotateToFeeder.omega);
      }
      else if(_robot_control_data.swerveInput.targetRightFeederAngle)
      {
        auto chassisRotateToFeeder =  m_rotateToFeeder.move(_swerve.GetPose(), frc::Pose2d(0.0_m, 0.0_m, frc::Rotation2d(ratbot::IntakeConfig::ROTATION_TO_FEEDER)));
        _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, chassisRotateToFeeder.omega);
        
      }
      else
      {
        m_rotateToFeeder.reset();
        if(_robot_control_data.swerveInput.goFieldOriented)
        {
          _swerve.SetRobotOriented();
            _swerve.Drive(0.0f, -_robot_control_data.swerveInput.yTranslation, 0.0f);
        }
        else
        {
          _swerve.SetFieldOriented();
            _swerve.Drive(_robot_control_data.swerveInput.xTranslation, _robot_control_data.swerveInput.yTranslation, _robot_control_data.swerveInput.rotation);
        }
    
      }

      if (_robot_control_data.resetNavx.reset)
      {
        _gyro.Reset();
      }
  }

  m_coralLauncherManager.HandleInput(_robot_control_data);
  m_algaeRemoverManager.HandleInput(_robot_control_data);
  m_ClimberManager.HandleInput(_robot_control_data);
  // End normal Teleop

  // else
  // {
  //   if (autonTimer.Get().value() <= 2.5)
  //   {
  //     _robot_control_data.algaeInput.RunRemoverTop = true;
  //     _robot_control_data.algaeInput.RunRemoverStow = false;
  //     _robot_control_data.algaeInput.RunRemoverBottom = false;
  //    m_algaeRemoverManager.HandleInput(_robot_control_data);
  //   }
  //   else
  //   {
  //     _robot_control_data.algaeInput.RunRemoverBottom = false;
  //     _robot_control_data.algaeInput.RunRemoverStow = true;
  //     _robot_control_data .algaeInput.RunRemoverTop = false;
  //     m_algaeRemoverManager.HandleInput(_robot_control_data);
  //   }

  //   if (autonTimer.Get().value() >= 3.48 && autonTimer.Get().value() <= 4.5)
  //   {
  //     _robot_control_data.coralInput.setFlywheelToL2Speed = true;
  //     _robot_control_data.coralInput.setFlywheelToL1Speed = false;
  //     _robot_control_data.coralInput.disableFlywheels = false;
  //     _robot_control_data.coralInput.indexerSpeeds = 1.0f;
  //     m_coralLauncherManager.HandleInput(_robot_control_data);
  //   }
  //   else
  //   {
  //       _robot_control_data.coralInput.disableFlywheels = true;
  //       _robot_control_data.coralInput.setFlywheelToL2Speed = false;
  //       _robot_control_data.coralInput.setFlywheelToL1Speed = false;
  //       _robot_control_data.coralInput.indexerSpeeds = 0.0f;

  //       m_coralLauncherManager.HandleInput(_robot_control_data);
  //   }
  // }
  

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
