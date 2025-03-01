#include "ControllerInterface.h"

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{
    UpdateSwerveInput(controlData);
    UpdateLauncherInput(controlData);
    UpdateSmartplannerInput(controlData);
};

void ControllerInterface::UpdateSwerveInput(RobotControlData &controlData)
{  
    controlData.swerveInput.xTranslation = -m_pilot.GetLeftY();
    controlData.swerveInput.yTranslation = -m_pilot.GetLeftX();
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
    controlData.coralInput.setFlywheelToL1Speed = m_pilot.GetAButton();
    controlData.coralInput.setFlywheelToL2Speed = m_pilot.GetBButton();
    controlData.coralInput.disableFlywheels = m_pilot.GetYButton();
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