#pragma once

#include "HAL/CoralLauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>

class CoralLauncherManager
{
public:
    CoralLauncherManager();
    ~CoralLauncherManager() = default;

    void HandleInput(RobotControlData& control_data);
    double GetRightWheelSpeed();
    double GetLeftWheelSpeed();
    void ResetStates(bool resetL1, bool resetL2, bool resetIndexer);

private:
    void L1Launch();
    void L2Launch();
    void IndexerLaunch();
    CoralLauncher m_CoralLauncher;
    int m_l1LaunchState = 0;
    frc::Timer m_Timer = frc::Timer();
    double m_l1LaunchSpeed = 1.0;
    double m_l2LaunchSpeed = 1.0;
    int m_l2LaunchState = 0;
    int m_indexerState = 0;

    frc::DigitalInput m_beam_break{9};
};