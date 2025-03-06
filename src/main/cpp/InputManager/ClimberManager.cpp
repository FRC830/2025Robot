#include "InputManager/ClimberManager.h"


// void ClimberManager::HandleInput(RobotControlData &robotControlData){
//     if (m_isFirstIteration)
//     {
//         m_matchTimer.Restart();
//         m_isFirstIteration = false;
//     }
//     if((robotControlData.climberInput.run && robotControlData.climberInput.run != m_prevClimberRun) && m_matchTimer.HasElapsed(150_s)){
//         m_climberTimer.Reset();
//         m_prevClimberRun = m_climberRun;
//         m_climberRun = true;
//     }

//     if(m_climberRun){
//         if (m_climberTimer.GetTimestamp() > m_climberDuration)
//         {
//             m_Climber.SetClimberSpeed(0.0);
//             return;
//         }
//         m_Climber.SetClimberSpeed(m_climberMotorSpeed);
//         m_prevClimberRun = robotControlData.climberInput.run;
//     }
    
//     robotControlData.climberOutput.ClimberSpeed = m_Climber.GetClimberSpeed();
// }

void ClimberManager::HandleInput(RobotControlData &robotControlData)
{
    if (/*controler says left*/)
    {
        m_Climber.SetClimberSpeed(1)
    }
    else if (/*controller says right*/)
    {
        m_Climber.SetClimberSpeed(-1)
    }
    else
    {
        // stop
    }
}

void ClimberManager::ResetState(){
    m_climberRun = false;
    m_prevClimberRun = false;
    m_climberTimer.Reset();
    m_isFirstIteration = true;
}