#pragma once
#include <frc/XboxController.h>
#include "RobotControlData.h"

class AlgaeRemover
{
    public:
        AlgaeRemover() = default;
        ~AlgaeRemover() = default;
        void SetPivotAngle(double angle);
        void SetWheelSpeed(double speed);
        double GetPivotAngle();
        double GetWheelSpeed();
    private:
        double pivotAngle = 0.0;
        double wheelSpeed = 0.0;
        double pullingWheelSpeed;
        

};