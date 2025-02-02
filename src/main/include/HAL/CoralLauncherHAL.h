#pragma once
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include <frc/Timer.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

class CoralLauncher
{
    public:
        CoralLauncher() = default;
        ~CoralLauncher() = default; 
        void L1Launch();
        void L2Launch();
        void IndexerLaunch();
        void SetRightWheelSpeed(double speed);
        void SetLeftWheelSpeed(double speed);
        void SetIndexerSpeed(double speed);
        double GetRightWheelSpeed();
        double GetLeftWheelSpeed();
        void ResetL1LaunchState();
        void ResetL2LaunchState();
        void ResetIndexerState();
        void HandleInput(RobotControlData& input);


    private:
        rev::spark::SparkMax rightMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax leftMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax indexer{0, rev::spark::SparkMax::MotorType::kBrushless};
        double m_RightWheelSpeed;
        double m_LeftWheelSpeed;
        double indexerSpeed;
        int m_l1LaunchState = 0;
        frc::Timer m_Timer = frc::Timer();
        double m_l1LaunchSpeed = 1.0;
        double m_l2LaunchSpeed = 1.0;
        int m_l2LaunchState = 0;
        int m_indexerState = 0;

        frc::DigitalInput m_beam_break{9};                                

};