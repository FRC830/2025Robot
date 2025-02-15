#include "ControllerInterface.h"

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData)
{
    UpdateSwerveInput(controlData);
    UpdateLauncherInput(controlData);
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
    controlData.launcherInput.goToL1 = m_pilot.GetAButton();
    controlData.launcherInput.goToL2 = m_pilot.GetAButton();
}