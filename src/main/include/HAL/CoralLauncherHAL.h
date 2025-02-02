#pragma once
#include "RobotControlData.h"
#include "rev/SparkMax.h"

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
        rev::spark::SparkMax rightMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax leftMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax indexer{0, rev::spark::SparkMax::MotorType::kBrushless};
        double m_RightWheelSpeed;
        double m_LeftWheelSpeed;
        double indexerSpeed;
};