#include "InputManager/ClimberManager.h"


void ClimberManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.climberInput.run && robotControlData.climberInput.run != m_prevClimberRun){
        m_climberTimer.Reset();
        m_prevClimberRun = m_climberRun;
        m_climberRun = true;
    }

    if(m_climberRun){
        if (m_climberTimer.GetTimestamp() > m_climberDuration)
        {
            m_Climber.SetClimberSpeed(0.0);
            return;
        }
        m_Climber.SetClimberSpeed(m_climberMotorSpeed);
        m_prevClimberRun = robotControlData.climberInput.run;
    }
    
    robotControlData.climberOutput.ClimberSpeed = m_Climber.GetClimberSpeed();

}

void ClimberManager::ResetState(){
    m_climberRun = false;
    m_climberTimer.Reset();
}