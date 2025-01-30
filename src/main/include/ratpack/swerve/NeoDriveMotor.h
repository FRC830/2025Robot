#pragma once

#include <rev/SparkMax.h>
#include "Interfaces/SwerveDriveMotor.h"
#include "units/velocity.h"
#include <rev/config/SparkMaxConfig.h>

struct SwerveDriveMotorConfig {
    int motorID;
    bool inverted;
    rev::spark::SparkMax *motor;
    rev::spark::SparkRelativeEncoder *encoder;
    rev::spark::SparkClosedLoopController *PID;
    rev::spark::SparkMaxConfig::IdleMode idleMode; 
    double p;
    double i;
    double d;
    double ff;
    double ratio;
    units::velocity::meters_per_second_t maxSpeed;
    double correction_factor;
    double drive_motor_current_limit;
    double swerve_voltage_compensation;
};

class NeoDriveMotor : public SwerveDriveMotor {

    public:
        NeoDriveMotor() = default; 
        virtual ~NeoDriveMotor() = default;
        virtual void Configure(SwerveDriveMotorConfig &config) override; 
        virtual void SetVelocity(units::velocity::feet_per_second_t v) override; 
        virtual units::velocity::feet_per_second_t GetVelocity() override; 
        virtual void SetIdleMode(bool m) override;
        virtual bool GetIdleMode() override; // just incase if we use motors other than the rev ones that use otehr than the rev stuff. idk 
        virtual units::foot_t GetPosition() override;



    private: 
        int m_motorID;
        bool m_inverted;
        rev::spark::SparkMax *m_motor;
        rev::spark::SparkRelativeEncoder *m_encoder;
        rev::spark::SparkClosedLoopController *m_PID;
        units::velocity::meters_per_second_t m_MaxSpeed;
        double m_correction_factor;
};
