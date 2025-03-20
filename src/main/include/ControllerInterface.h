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
        void UpdateLauncherInput(RobotControlData &controlData);
        void UpdateSmartplannerInput(RobotControlData &controlData);
        void UpdateAlgaeArmInput(RobotControlData &controlData);
        void UpdateClimberInput(RobotControlData &controlData);
        void UpdateNavxInput(RobotControlData &controlData);
        

        frc::XboxController m_pilot{0};
        frc::XboxController m_copilot{1};
        frc::Timer m_timer;
        int m_vibrateControllerState = 0;
        double m_slowmodefactor = 0.25;
        double m_globalDuration = 0.0;
        bool variable = false;
        bool m_prevLeftFeederButtonValue = false;
        bool m_prevRightFeederButtonValue = false;
};