#include "InputManager/ClimberManager.h"


void ClimberManager::HandleInput(RobotControlData &robotControlData)
{

    if(m_matchTimer.HasElapsed(0_s))
    {
        m_Climber.SetClimberSpeed(robotControlData.climberInput.ClimberSpeed);
    }
}

void ClimberManager::ResetState(){
    m_matchTimer.Reset();
    m_matchTimer.Start();
}