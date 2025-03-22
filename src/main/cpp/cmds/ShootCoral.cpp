#include "cmds/ShootCoral.h"
#include "MechanismConfig.h"

ShootCoral::ShootCoral(RobotControlData& data) : m_data(data)
{}

void ShootCoral::Initialize()
{
    m_data.coralInput.disableFlywheels = false;
    m_data.coralInput.setFlywheelToL1Speed = false;
    m_data.coralInput.setFlywheelToL2Speed = true;
    m_data.coralInput.indexerSpeeds = 0.0;
    m_state = 0;
    m_timer.Stop();
    m_timer.Reset();
    m_timer.Start();
}

void ShootCoral::Execute()
{
    switch(m_state)
    {
        case 0:
        {
            if (m_timer.Get().value() > 1.0)
            {
                m_state++;
            }
            break;
        }
        case 1:
        {
            m_data.coralInput.indexerSpeeds = 1.0;
            break;
        }
    }
}

bool ShootCoral::IsFinished()
{
    return (m_timer.Get().value() > 3.0);
}

void ShootCoral::End(bool interrupted)
{
    m_data.coralInput.disableFlywheels = true;
    m_data.coralInput.setFlywheelToL1Speed = false;
    m_data.coralInput.setFlywheelToL2Speed = false;
    m_data.coralInput.indexerSpeeds = 0.0;
    m_timer.Stop();
}