#pragma once
#include "RobotControlData.h"

class CoralLauncher
{
    public:
        CoralLauncher() = default;
        ~CoralLauncher() = default; 
        void SetRightWheelSpeed(double speed);
        void SetLeftWheelSpeed(double speed);
        void SetIndexerSpeed(double speed);
        double GetRightWheelSpeed();
        double GetLeftWheelSpeed();
    private:
};