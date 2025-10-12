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
    private:
    frc::XboxController LucasYuan{0};
    void UpdateLauncherInput(RobotControlData &controlData);
    
};
