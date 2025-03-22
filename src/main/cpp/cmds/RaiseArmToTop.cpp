#include "cmds/RaiseArmToBottom.h"
#include "MechanismConfig.h"

RaiseArmToBottom::RaiseArmToBottom(RobotControlData& data) : m_data(data)
{}

void RaiseArmToBottom::Initialize()
{
    m_data.algaeInput.RunRemoverTop = false;
    m_data.algaeInput.RunRemoverBottom = false;
    m_data.algaeInput.RunRemoverStow = false;
}

void RaiseArmToBottom::Execute()
{
    m_data.algaeInput.RunRemoverBottom = true;
}

bool RaiseArmToBottom::IsFinished()
{
    return m_data.algaeOutput.PivotAngle > ratbot::AlgaeRemoverConfig::Pivot::BOTTOM_REMOVER_POS;
}

void RaiseArmToBottom::End(bool interrupted)
{
}