#pragma once

#include "HAL/CoralLauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>


struct CoralInput{
    double leftSpeed;
    double rightSpeed;
    double indexSpeed;

    bool goToL1;
    bool goToL2;

    //todo
};

class CoralLauncherManager
{
public:
    CoralLauncherManager();
    ~CoralLauncherManager() = default;

   
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
    double m_l1LaunchSpeed = 1.0; //this is just default for now change later
    double m_l2LaunchSpeed = 1.0; //this is just default for now change later
    int m_l2LaunchState = 0;
    int m_indexerState = 0;
    bool m_goToL1;
    bool m_goTol2;
    double multiplier = 1.5; //this is just default for now change later
    frc::DigitalInput m_beam_break{9};
};