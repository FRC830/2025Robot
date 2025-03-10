#include "ControllerInterface.h"
#include <iostream>

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{
    UpdateSwerveInput(controlData);
    UpdateLauncherInput(controlData);
    UpdateSmartplannerInput(controlData);
    UpdateClimberInput(controlData);

    // code for the VibrateController function
    if (m_timer.Get().value()>=m_globalDuration)
    {
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0.0);
        m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
    }
};
void ControllerInterface::UpdateClimberInput(RobotControlData &controlData)
{
    // if ((m_copilot.GetRightY() > 0.1)||(m_copilot.GetLeftY() > 0.1)){
    //     controlData.climberInput.Unspool = true;
    //     controlData.climberInput.Respool = false;
    // }
    // else if ((m_copilot.GetRightY() < -0.1)||(m_copilot.GetLeftY() < -0.1)){
    //     controlData.climberInput.Unspool = false;
    //     controlData.climberInput.Respool = true;
    // }
    // else{
    //     controlData.climberInput.Unspool = false;
    //     controlData.climberInput.Respool = false;
    // }
    if (std::fabs(m_copilot.GetRightY()) > 0.1)
    {
        controlData.climberInput.ClimberSpeed = m_copilot.GetRightY();
    }
    else
    {
        controlData.climberInput.ClimberSpeed = 0;
    }
}

void ControllerInterface::UpdateSwerveInput(RobotControlData &controlData)
{  
    controlData.swerveInput.xTranslation = m_pilot.GetLeftY();
    controlData.swerveInput.yTranslation = m_pilot.GetLeftX();
    controlData.swerveInput.rotation = -m_pilot.GetRightX();

    auto tempTargetLeftFeeder = m_pilot.GetLeftTriggerAxis() > 0.1;
    auto tempTargetRightFeeder = m_pilot.GetRightTriggerAxis() > 0.1;

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

void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData){
    controlData.coralInput.setFlywheelToL1Speed = m_copilot.GetAButton();
    controlData.coralInput.setFlywheelToL2Speed = m_copilot.GetBButton();
    controlData.coralInput.disableFlywheels = m_copilot.GetYButton();

    if (m_copilot.GetXButton())
    {
        controlData.coralInput.indexerSpeeds = 0.7f;
    }
    else
    {
        controlData.coralInput.indexerSpeeds = 0.0f;
    }

    static constexpr double RATIO = 0.3f;
    auto indexerSpeed = m_copilot.GetLeftY() * RATIO;
    if (std::fabs(indexerSpeed) < 0.05f)
    {
        indexerSpeed = 0.0f;
    }
    controlData.coralInput.indexerSpeeds = indexerSpeed;
}

void ControllerInterface::UpdateSmartplannerInput(RobotControlData &controlData)
{
    if (m_copilot.GetLeftTriggerAxis() > 0.1) {controlData.plannerInput.Left_L1 = true;}
    else if (m_copilot.GetRightTriggerAxis() > 0.1) {controlData.plannerInput.Right_L1 = true;}
    else if (m_copilot.GetLeftBumperButtonPressed()) {controlData.plannerInput.Left_L2 = true;}
    else if (m_copilot.GetRightBumperButtonPressed()) {controlData.plannerInput.Right_L2 = true;}
    else 
    {
        controlData.plannerInput.Left_L1 = false;
        controlData.plannerInput.Left_L2 = false;
        controlData.plannerInput.Right_L1 = false;
        controlData.plannerInput.Right_L2 = false;
    }

}

void ControllerInterface::VibrateController(double intensity, double duration)
{
    m_globalDuration = duration;
    m_timer.Restart();
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, intensity);
    m_pilot.SetRumble(frc::GenericHID::RumbleType::kRightRumble, intensity);
}
