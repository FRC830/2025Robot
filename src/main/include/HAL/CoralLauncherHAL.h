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
        void L1Launch();
        void L2Launch();
        void IndexerLaunch();
        void SetWheelSpeeds(double rightSpeed, double leftSpeed);
        void SetIndexerSpeed(double indexerSpeed);
        double GetRightWheelSpeed();
        double GetLeftWheelSpeed();
        bool AreFlywheelsAtDesiredSpeed();
        bool BeamBreakStatus();
    private:
        rev::spark::SparkMax rightMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax leftMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax indexer{0, rev::spark::SparkMax::MotorType::kBrushless};
        frc::DigitalInput m_beam_break{9}; //moved from CoralLauncherManager; move back if needed
        double m_RightWheelSpeed;
        double desiredRightSpeed;
        double m_LeftWheelSpeed;
        double desiredLeftSpeed;
        double m_IndexerSpeed;    
        double num = 0.001; //change variable name accordingly; make a more suitable name                            
};