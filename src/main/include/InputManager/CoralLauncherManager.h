#pragma once

#include "HAL/CoralLauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>


class CoralLauncherManager
{
public:
    CoralLauncherManager();
    ~CoralLauncherManager() = default;

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
private:
    CoralLauncher m_CoralLauncher;
    bool m_setFlywheelToL1Speed = false;
    bool m_setFlywheelToL2Speed = false;
};