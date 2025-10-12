#pragma once
#include <frc/XboxController.h>
#include "RobotControlData.h"
#include <frc/Timer.h>

class ControllerInterface
{
    public:
        ControllerInterface() = default;
        ~ControllerInterface() = default;
        void UpdateRobotControlData(RobotControlData &ControlData);
    private:
        frc::XboxController DavesController{0};
        void UpdateLauncherInput(RobotControlData &ControlData);
};
