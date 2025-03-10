#pragma once

#include "HAL/ClimberHAL.h"
#include "RobotControlData.h"
#include <frc/Timer.h>


class ClimberManager
{
public:
    ClimberManager() = default;
    ~ClimberManager() = default;
    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
private:
    Climber m_Climber;
    frc::Timer m_matchTimer;
};