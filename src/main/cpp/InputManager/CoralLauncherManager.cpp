#include "InputManager/CoralLauncherManager.h"


void CoralLauncherManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.coralInput.setFlywheelToL1Speed){
        m_setFlywheelToL1Speed = true;
        m_setFlywheelToL2Speed = false;
        m_setFlywheelToZeroSpeed = false;
    }else if (robotControlData.coralInput.setFlywheelToL2Speed){
        m_setFlywheelToL1Speed = false;
        m_setFlywheelToL2Speed = true;
        m_setFlywheelToZeroSpeed = false;
    }else if (robotControlData.coralInput.disableFlywheels){
        m_setFlywheelToL1Speed = false;
        m_setFlywheelToL2Speed = false;
        m_setFlywheelToZeroSpeed = true;
    }

    if(m_setFlywheelToL1Speed){
        m_CoralLauncher.SetWheelSpeeds(500.0, 700.0); //configure speeds
    }
    if(m_setFlywheelToL2Speed){
        m_CoralLauncher.SetWheelSpeeds(1050.0, 1050.0); //config speeds
    }
    if(m_setFlywheelToZeroSpeed){
        m_CoralLauncher.SetWheelSpeeds(0.0,0.0);
    }
    m_CoralLauncher.SetIndexerSpeeds(robotControlData.coralInput.indexerSpeeds);
    // if(m_CoralLauncher.BeamBreakStatus()){
    //     m_CoralLauncher.SetWheelSpeeds(0,0);
    // }
    robotControlData.coralOutput.isBeamBroken = m_CoralLauncher.BeamBreakStatus();
    robotControlData.coralOutput.leftSpeed = m_CoralLauncher.GetLeftWheelSpeed();
    robotControlData.coralOutput.rightSpeed = m_CoralLauncher.GetRightWheelSpeed();
    robotControlData.coralOutput.flywheelsAtSpeed = m_CoralLauncher.AreFlywheelsAtDesiredSpeed();
}

void CoralLauncherManager:: ResetState(){
    m_setFlywheelToL1Speed = false;
    m_setFlywheelToL2Speed = false;
    m_setFlywheelToZeroSpeed = true;
}
