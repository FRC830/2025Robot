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
    int m_l1LaunchState = 0;
    int m_l2LaunchState = 0;
    int m_indexerState = 0;
    bool m_setFlywheelToL1Speed = false;
    bool m_setFlywheelToL2Speed = false;
};