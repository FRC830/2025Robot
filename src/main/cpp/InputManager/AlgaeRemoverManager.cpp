#include "InputManager/AlgaeRemoverManager.h"


void AlgaeRemoverManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.algaeInput.RunRemoverTop && robotControlData.algaeInput.RunRemoverTop != m_prevAngleToTop){
        m_removerTimer.Reset();
        m_pivotAngleToTop = true;
        m_prevAngleToTop != m_prevAngleToTop; 
        m_pivotAngleToBottom = false;
    }else if (robotControlData.algaeInput.RunRemoverBottom && robotControlData.algaeInput.RunRemoverBottom != m_prevAngleToBottom){
        m_removerTimer.Reset();
        m_pivotAngleToTop = false;
        m_pivotAngleToBottom = true;
        m_prevAngleToBottom != m_prevAngleToBottom; 
    }

    if(m_pivotAngleToTop){
        m_AlgaeRemover.ProfiledMoveToAngle(m_pivotAngleToRemoveTop); 
        if (m_removerTimer.GetTimestamp() > m_RemoverTime)
        {
            m_AlgaeRemover.SetRemoverSpeed(0.0);
        }
        m_AlgaeRemover.SetRemoverSpeed(m_RemoverSpeed);
    }
    if(m_pivotAngleToBottom){
        m_AlgaeRemover.ProfiledMoveToAngle(m_pivotAngleToRemoveBottom);
        if (m_removerTimer.GetTimestamp() > m_RemoverTime)
        {
            m_AlgaeRemover.SetRemoverSpeed(0.0);
        }
        m_AlgaeRemover.SetRemoverSpeed(-m_RemoverSpeed);
    }
    
    robotControlData.algaeOutput.RemoverSpeed = m_AlgaeRemover.GetWheelSpeed();
    robotControlData.algaeOutput.PivotAngle = m_AlgaeRemover.GetPivotAngle();

}

void AlgaeRemoverManager::ResetState(){
    m_pivotAngleToBottom = false;
    m_pivotAngleToTop = false;
    m_removerTimer.Reset();
}