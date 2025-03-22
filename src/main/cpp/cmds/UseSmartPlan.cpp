#include "cmds/UseSmartPlan.h"
#include "MechanismConfig.h"

UseSmartPlan::UseSmartPlan(RobotControlData& data) : m_data(data)
{}

void UseSmartPlan::Initialize()
{
    m_data.plannerInput.Left_L1 = false;
    m_data.plannerInput.Right_L1 = false;
    m_data.plannerInput.Left_L2 = false;
    m_data.plannerInput.Right_L2 = false;
}

void UseSmartPlan::Execute()
{
    m_data.plannerInput.Right_L2 = true;
}

bool UseSmartPlan::IsFinished()
{
    return false;
}

void UseSmartPlan::End(bool interrupted)
{
}