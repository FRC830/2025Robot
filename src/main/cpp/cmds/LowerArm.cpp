#include "cmds/LowerArm.h"
#include "MechanismConfig.h"

LowerArm::LowerArm(RobotControlData& data) : m_data(data)
{}

void LowerArm::Initialize()
{
    m_data.algaeInput.RunRemoverTop = false;
    m_data.algaeInput.RunRemoverBottom = false;
    m_data.algaeInput.RunRemoverStow = false;
}

void LowerArm::Execute()
{
    m_data.algaeInput.RunRemoverStow = true;
}

bool LowerArm::IsFinished()
{
    return m_data.algaeOutput.PivotAngle <= ratbot::AlgaeRemoverConfig::Pivot::STOW_REMOVER_POS;
}

void LowerArm::End(bool interrupted)
{
}