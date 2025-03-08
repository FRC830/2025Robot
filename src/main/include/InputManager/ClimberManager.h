#pragma once

#include "HAL/ClimberHAL.h"
#include "RobotControlData.h"
#include <frc/Timer.h>
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
};