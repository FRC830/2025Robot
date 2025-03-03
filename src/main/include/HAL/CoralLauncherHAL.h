#pragma once
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

class CoralLauncher
{
    public:
        CoralLauncher();
        ~CoralLauncher() = default; 
        void SetWheelSpeeds(double rightSpeed, double leftSpeed);
        void SetIndexerSpeeds(double indexerSpeed);
        double GetRightWheelSpeed();
        double GetLeftWheelSpeed();
        bool AreFlywheelsAtDesiredSpeed();
        bool BeamBreakStatus();
    private:
        rev::spark::SparkMax m_rightMotor{30, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_leftMotor{31, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_indexer1{32, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_indexer2{33, rev::spark::SparkMax::MotorType::kBrushless};
        frc::DigitalInput m_beam_break{34}; //moved from CoralLauncherManager; move back if needed
        double m_desiredRightSpeed;
        double m_desiredLeftSpeed; 
        const double SMALL_NUM = 0.001; //change variable name accordingly; make a more suitable name                            
};