#include "InputManager/AlgaeRemoverManager.h"
#include "MechanismConfig.h"

void AlgaeRemoverManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.algaeInput.RunRemoverTop){
        m_pivotAngleToTop = true;
        m_pivotAngleToBottom = false;
        m_pivotAngleToStow = true;
    }else if (robotControlData.algaeInput.RunRemoverBottom){
        m_pivotAngleToTop = false;
        m_pivotAngleToBottom = true;
        m_pivotAngleToStow = true;
    }else if (robotControlData.algaeInput.RunRemoverStow){
        m_pivotAngleToTop = false;
        m_pivotAngleToBottom = false;
        m_pivotAngleToStow = true;
    }

    if(m_pivotAngleToTop){
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::TOP_REMOVER_POS); ;
        m_AlgaeRemover.SetRemoverSpeed(ratbot::AlgaeRemoverConfig::Remover::REMOVER_SPEED);
    }
    if(m_pivotAngleToBottom){
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::BOTTOM_REMOVER_POS);
        m_AlgaeRemover.SetRemoverSpeed(-ratbot::AlgaeRemoverConfig::Remover::REMOVER_SPEED);
    }
    if(m_pivotAngleToStow){
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::STOW_REMOVER_POS);
        m_AlgaeRemover.SetRemoverSpeed(0.0);
    }
    
    robotControlData.algaeOutput.RemoverSpeed = m_AlgaeRemover.GetWheelSpeed();
    robotControlData.algaeOutput.PivotAngle = m_AlgaeRemover.GetPivotAngle();

}

void AlgaeRemoverManager::ResetState(){
    m_pivotAngleToBottom = false;
    m_pivotAngleToTop = false;
    m_pivotAngleToStow = true;
}