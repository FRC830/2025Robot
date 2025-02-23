#include "ControllerInterface.h"
#include <iostream>

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{
    UpdateSwerveInput(controlData);
};

void ControllerInterface::UpdateSwerveInput(RobotControlData &controlData)
{  
    controlData.swerveInput.xTranslation = -m_pilot.GetLeftY();
    controlData.swerveInput.yTranslation = -m_pilot.GetLeftX();
    controlData.swerveInput.rotation = -m_pilot.GetRightX();

    auto tempTargetLeftFeeder = m_pilot.GetLeftTriggerAxis() > 0.1;
    auto tempTargetRightFeeder = m_pilot.GetRightTriggerAxis() > 0.1;

    if (m_pilot.GetAButton())
    {
        VibrateController(0.5, 0.5);
    }
    if (tempTargetLeftFeeder && !m_prevLeftFeederButtonValue)
    {
        controlData.swerveInput.targetLeftFeederAngle = !controlData.swerveInput.targetLeftFeederAngle;
        controlData.swerveInput.targetRightFeederAngle = false;
    }

    if (tempTargetRightFeeder && !m_prevRightFeederButtonValue)
    {
        controlData.swerveInput.targetRightFeederAngle = !controlData.swerveInput.targetRightFeederAngle;
        controlData.swerveInput.targetLeftFeederAngle = false;
    }

    m_prevLeftFeederButtonValue = tempTargetLeftFeeder;
    m_prevRightFeederButtonValue = tempTargetRightFeeder;

}

void ControllerInterface::VibrateController(double intensity, double duration)
{
    switch (VibrateControllerState)
    {
    case 0:
        m_timer.Start();
        std::cout << VibrateControllerState << " << 0, ";
        VibrateControllerState++;
        break;
    case 1:
        if (!m_timer.HasElapsed(duration*1_s))
        {
            m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, intensity);
            m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, intensity);
            std::cout << VibrateControllerState << " << 1, ";
        }
        else
        {
            VibrateControllerState++;
            std::cout << VibrateControllerState << " << 2, ";
        }
        break;
    case 2:
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0.0);
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
        m_timer.Stop();
        m_timer.Reset();
        VibrateControllerState = 0;
        std::cout << VibrateControllerState << " << 3, ";
        break;
    default:
        break;
    }
    m_timer.Start();
    variable == true;
    if (!m_timer.HasElapsed(duration*1_s))
    {
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, intensity);
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, intensity);
    }
    else
    {
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0.0);
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
        m_timer.Stop();
        m_timer.Reset();
    }
    std::cout << VibrateControllerState << std::endl;
}
