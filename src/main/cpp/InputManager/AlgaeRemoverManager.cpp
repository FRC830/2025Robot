#include "InputManager/AlgaeRemoverManager.h"


void AlgaeRemoverManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.algaeInput.RunRemoverTop){
        m_pivotAngleToTop = true;
        m_pivotAngleToBottom = false;
    }else if (robotControlData.algaeInput.RunRemoverBottom){
        m_pivotAngleToTop = false;
        m_pivotAngleToBottom = true;
    }

    if(m_pivotAngleToTop){
        m_AlgaeRemover.ProfiledMoveToAngle(m_pivotAngleToRemoveTop); 
        m_removerTimer.Reset();
        if (m_removerTimer.GetTimestamp() > m_RemoverTime)
        {
            m_AlgaeRemover.SetRemoverSpeed(0.0);
        }
        m_AlgaeRemover.SetRemoverSpeed(m_RemoverSpeed);
    }
    if(m_pivotAngleToBottom){
        m_AlgaeRemover.ProfiledMoveToAngle(m_pivotAngleToRemoveBottom);
        m_removerTimer.Reset();
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