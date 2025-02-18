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
}

void CoralLauncherManager::ResetState(){
    m_l1LaunchState = 0;
    m_l2LaunchState = 0;
    m_setFlywheelToL1Speed = false;
    m_setFlywheelToL2Speed = false;
}
//void CoralLauncherManager::IndexerLaunch()
// {
//     switch(m_indexerState)
//     {
//         case 0:
//         {
//             m_Timer.Stop();
//             m_Timer.Reset();
//             m_Timer.Start();

//             m_indexerState++;
//             break;
//         }

//         case 1:
//         {
//             if(!m_beam_break.Get())
//             {
//                 m_indexerState++;
//                 break;
//             }
//             SetIndexerSpeed(1.0);
//         }

//         case 2:
//         {
//             SetIndexerSpeed(0);
//             break;
//         }
//     }
// }

// void CoralLauncherManager::ResetStates(bool resetL1, bool resetL2, bool resetIndexer)
// {
//     if(resetL1)
//     {
//         m_l1LaunchState = 0;
//     }
//     if(resetL2)
//     {
//         m_l2LaunchState = 0;
//     }
//     if(resetIndexer)
//     {
//         m_indexerState = 0;
//     }
// }