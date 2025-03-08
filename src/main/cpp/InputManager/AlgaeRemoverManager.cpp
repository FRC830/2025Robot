#include "InputManager/AlgaeRemoverManager.h"
#include "MechanismConfig.h"

void AlgaeRemoverManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.algaeInput.RunRemoverTop){
        m_pivotAngleToTop = true;
        m_pivotAngleToBottom = false;
    }else if (robotControlData.algaeInput.RunRemoverBottom){
        m_pivotAngleToTop = false;
        m_pivotAngleToBottom = true;
    }

    if(m_pivotAngleToTop){
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::m_pivotAngleToRemoveTop); ;
        m_AlgaeRemover.SetRemoverSpeed(ratbot::AlgaeRemoverConfig::Remover::REMOVER_SPEED);
    }
    if(m_pivotAngleToBottom){
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::m_pivotAngleToRemoveBottom);
        m_AlgaeRemover.SetRemoverSpeed(-ratbot::AlgaeRemoverConfig::Remover::REMOVER_SPEED);
    }
    
    robotControlData.algaeOutput.RemoverSpeed = m_AlgaeRemover.GetWheelSpeed();
    robotControlData.algaeOutput.PivotAngle = m_AlgaeRemover.GetPivotAngle();

}

void AlgaeRemoverManager::ResetState(){
    m_pivotAngleToBottom = false;
    m_pivotAngleToTop = false;
}