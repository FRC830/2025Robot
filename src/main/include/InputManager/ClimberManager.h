#pragma once

#include "HAL/ClimberHAL.h"
#include "RobotControlData.h"
// #include <frc/DigitalInput.h>


class ClimberManager
{
public:
    ClimberManager();
    ~ClimberManager() = default;
    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
private:
    Climber m_Climber;
    frc::Timer m_matchTimer;
    bool m_isFirstIteration = true;
    bool m_prevClimberRun;
    bool m_climberRun;
    frc::Timer m_climberTimer;
    units::second_t m_climberDuration = 4.0_s; //to be changed
    double m_climberMotorSpeed = 3; //to be changed!! 
};