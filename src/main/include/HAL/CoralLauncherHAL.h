#pragma once
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

class CoralLauncher
{
    public:
        CoralLauncher(); // BBC
        ~CoralLauncher() = default; 
        void L1Launch();
        void L2Launch();
        void IndexerLaunch();
        void SetWheelSpeeds(double rightSpeed, double leftSpeed);
        void SetIndexerSpeed(double indexerSpeed);
        double GetRightWheelSpeed();
        double GetLeftWheelSpeed();
    private:
        rev::spark::SparkMax rightMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax leftMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax indexer{0, rev::spark::SparkMax::MotorType::kBrushless};
        double m_RightWheelSpeed;
        double m_LeftWheelSpeed;
        double m_IndexerSpeed;                                
};