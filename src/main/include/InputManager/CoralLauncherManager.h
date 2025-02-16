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
    // void L1Launch();
    // void L2Launch();
    // void IndexerLaunch();
    CoralLauncher m_CoralLauncher;
    double m_l1LaunchSpeed = 1.0; //this is just default for now change later
    double m_l2LaunchSpeed = 1.0; //this is just default for now change later
    int m_l2LaunchState = 0;
    int m_indexerState = 0;
    bool m_setFlywheelToL1Speed;
    bool m_setFlywheelToL2Speed;
    double multiplier = 1.5; //this is just default for now change later
    frc::DigitalInput m_beam_break{9};
};