#pragma once

#include "Interfaces/SwerveTurnMotor.h"
#include "Interfaces/SwerveAbsoluteEncoder.h"
#include "rev/SparkMax.h"
#include "rev/SparkClosedLoopController.h"

struct SwerveTurnMotorConfig{
    SwerveAbsoluteEncoder *absouluteEncoder; 
    int deviceID;
    bool inverted; 
    rev::spark::SparkMax *turn_motor; 
    rev::spark::SparkRelativeEncoder *relative_Encoder;
    rev::spark::SparkClosedLoopController *PID;
    double p;
    double i;
    double d;
    double ff;
    double ratio;
    int turn_motor_current_limit;
    double swerve_voltage_compensation;
};

class NeoTurnMotor : public SwerveTurnMotor {

    public:
        NeoTurnMotor() = default;
        virtual ~NeoTurnMotor() = default;
        virtual void Configure(SwerveTurnMotorConfig &config) override;
        virtual void SetRotation(frc::Rotation2d deg) override; 
        virtual frc::Rotation2d GetRotation() override; 
        virtual bool GetInverted() override; 
        virtual void SetInverted(bool invert) override; 
        virtual void ForceTurnDirectionCW() override; 
        virtual void ForceTurnDirectionCCW() override; 

    private: 
       SwerveAbsoluteEncoder *m_AbsouluteEncoder;
       rev::spark::SparkMax *m_turn_motor; 
       rev::spark::SparkRelativeEncoder *m_relative_Encoder;
       rev::spark::SparkClosedLoopController *m_PID; 
       double m_pastCommandAngle;
};