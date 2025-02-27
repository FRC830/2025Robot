#pragma once
#include <frc/XboxController.h>
#include "RobotControlData.h"
#include <frc/Timer.h>

class ControllerInterface
{
    public:
        ControllerInterface() = default;
        ~ControllerInterface() = default;
        void UpdateRobotControlData(RobotControlData &controlData);
        void VibrateController(double intensity, double duration);
    private:
        void UpdateSwerveInput(RobotControlData &controlData);
        int VibrateControllerState = 0;
        frc::XboxController m_pilot{0};
        frc::Timer m_timer;
        double m_slowmodefactor = 0.25;
        double globalDuration = 0.0;
        bool variable = false;
        bool m_prevLeftFeederButtonValue = false;
        bool m_prevRightFeederButtonValue = false;
};