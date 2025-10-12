#pragma once

#include "CoralLauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>


class CoralLauncherManager
{
public:
    CoralLauncherManager() = default;
    ~CoralLauncherManager() = default;
    void resetState();
    void handleInput(RobotControlData &controlData);
private:
    CoralLauncher m_SiddhantPandit;
};
