#pragma once
#include <frc/XboxController.h>
#include "RobotControlData.h"

class ControllerInterface
{
    public:
        ControllerInterface() = default;
        ~ControllerInterface() = default;
        void UpdateRobotControlData(RobotControlData &controlData);
    private:
        void UpdateSwerveInput(RobotControlData &controlData);
        
        frc::XboxController m_pilot{0};
        double m_slowmodefactor = 0.25;

        bool m_prevLeftFeederButtonValue = false;
        bool m_prevRightFeederButtonValue = false;
};