#include "cmds/RaiseArm.h"
#include "MechanismConfig.h"

RaiseArm::RaiseArm(RobotControlData& data) : m_data(data)
{}

void RaiseArm::Initialize()
{
    m_data.algaeInput.RunRemoverTop = false;
    m_data.algaeInput.RunRemoverBottom = false;
    m_data.algaeInput.RunRemoverStow = false;
}

void RaiseArm::Execute()
{
    m_data.algaeInput.RunRemoverTop = true;
}

bool RaiseArm::IsFinished()
{
    return m_data.algaeOutput.PivotAngle > ratbot::AlgaeRemoverConfig::Pivot::TOP_REMOVER_POS;
}

void RaiseArm::End(bool interrupted)
{
}