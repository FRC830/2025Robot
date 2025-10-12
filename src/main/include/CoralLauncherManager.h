#pragma once

#include "CoralLauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>


class CoralLauncherManager
{
public:
    CoralLauncherManager() = default;
    ~CoralLauncherManager() = default;
    void ResetState(RobotControlData &controlData);
    void HandleInput(RobotControlData &controlData);


private:
    CoralLauncher m_launcher; // m_ means member variable
};
