#include "InputManager/AlgaeRemoverManager.h"
#include "MechanismConfig.h"
#include <iostream>
#include <MechanismConfig.h>

void AlgaeRemoverManager::HandleInput(RobotControlData &robotControlData){
    
    
    if(robotControlData.algaeInput.RunRemoverTop)
    { //up
        m_pivotAngleToTop = true;
        m_pivotAngleToBottom = false;
        m_pivotAngleToStow = false;
        m_AlgaeRemover.PivotAngleToTop();
        m_AlgaeRemover.SetRemoverSpeed(1.0);
        //std::cout << "run remover top" << std::endl;
    }
    if (robotControlData.algaeInput.RunRemoverBottom)
    { //down
        m_pivotAngleToTop = false;
        m_pivotAngleToBottom = true;
        m_pivotAngleToStow = false;
        m_AlgaeRemover.PivotAngleToBottom();
        m_AlgaeRemover.SetRemoverSpeed(1.0);
        //std::cout << "run remover bottom" << std::endl;
    }
    if (robotControlData.algaeInput.RunRemoverStow)
    { //stop
        m_pivotAngleToTop = false;
        m_pivotAngleToBottom = false;
        m_pivotAngleToStow = true;
        m_AlgaeRemover.PivotAngleToStow();
        m_AlgaeRemover.SetRemoverSpeed(0.0);
        //std::cout << "stop arm" << std::endl;
    }
    

/*
    if(m_pivotAngleToTop){
       // std::cout << "starting move" << std::endl;
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::TOP_REMOVER_POS); 
        m_AlgaeRemover.SetRemoverSpeed(ratbot::AlgaeRemoverConfig::Remover::REMOVER_SPEED);
       // std::cout << "going to the top" << std::endl;
    }
    if(m_pivotAngleToBottom){
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::BOTTOM_REMOVER_POS);
        m_AlgaeRemover.SetRemoverSpeed(-ratbot::AlgaeRemoverConfig::Remover::REMOVER_SPEED);
    }
    if(m_pivotAngleToStow){
        m_AlgaeRemover.ProfiledMoveToAngle(ratbot::AlgaeRemoverConfig::Pivot::STOW_REMOVER_POS);
        m_AlgaeRemover.SetRemoverSpeed(0.0);
    }
    
*/
    robotControlData.algaeOutput.RemoverSpeed = m_AlgaeRemover.GetWheelSpeed();
    robotControlData.algaeOutput.PivotAngle = m_AlgaeRemover.GetPivotAngle();
}

void AlgaeRemoverManager::ResetState(RobotControlData &robotControlData){
    robotControlData.algaeInput.RunRemoverBottom = false;
    robotControlData.algaeInput.RunRemoverStow = true;
    robotControlData.algaeInput.RunRemoverTop = false;
    m_pivotAngleToBottom = false;
    m_pivotAngleToTop = false;
    m_pivotAngleToStow = true;
    m_AlgaeRemover.ResetState();
    m_AlgaeRemover.MoveArm(0);
}