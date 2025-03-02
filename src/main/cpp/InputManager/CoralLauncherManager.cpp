#include "InputManager/CoralLauncherManager.h"


void CoralLauncherManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.coralInput.setFlywheelToL1Speed){
        m_setFlywheelToL1Speed = true;
        m_setFlywheelToL2Speed = false;
    }else if (robotControlData.coralInput.setFlywheelToL2Speed){
        m_setFlywheelToL1Speed = false;
        m_setFlywheelToL2Speed = true;
    }

    if(m_setFlywheelToL1Speed){
        m_CoralLauncher.SetWheelSpeeds(1.0,1.0); //configure speeds
    }
    if(m_setFlywheelToL2Speed){
        m_CoralLauncher.SetWheelSpeeds(1.0,1.0); //config speeds
    }
    m_CoralLauncher.SetIndexerSpeeds(robotControlData.coralInput.indexerSpeeds);
    if(m_CoralLauncher.BeamBreakStatus()){
        m_CoralLauncher.SetWheelSpeeds(0,0);
    }
    robotControlData.coralOutput.isBeamBroken = m_CoralLauncher.BeamBreakStatus();
    robotControlData.coralOutput.leftSpeed = m_CoralLauncher.GetLeftWheelSpeed();
    robotControlData.coralOutput.rightSpeed = m_CoralLauncher.GetRightWheelSpeed();
    robotControlData.coralOutput.flywheelsAtSpeed = m_CoralLauncher.AreFlywheelsAtDesiredSpeed();
    if(robotControlData.coralInput.disableFlywheels){
        m_CoralLauncher.SetWheelSpeeds(0,0);
    }

}

void CoralLauncherManager::ResetState(){
    m_setFlywheelToL1Speed = false;
    m_setFlywheelToL2Speed = false;
}
