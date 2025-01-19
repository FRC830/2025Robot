#include "ratpack/swerve/NeoDriveMotor.h"
#include "ratpack/SparkMaxDebugMacro.h"
#include <rev/config/SparkMaxConfig.h>

void NeoDriveMotor::Configure(SwerveDriveMotorConfig &config){
    m_encoder = config.encoder;
    m_motorID = config.motorID;
    m_motor = config.motor;
    m_PID = config.PID;

    rev::spark::SparkMaxConfig mtr_config{};

    mtr_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    mtr_config.closedLoop.Pidf(config.p, config.i, config.d, config.ff);
    mtr_config.encoder.VelocityConversionFactor(config.ratio);
    mtr_config.encoder.PositionConversionFactor((config.ratio*60));
    mtr_config.Inverted(config.inverted);
    mtr_config.SetIdleMode(config.idleMode);
    mtr_config.SmartCurrentLimit(config.drive_motor_current_limit);
    mtr_config.VoltageCompensation(config.swerve_voltage_compensation);

    START_RETRYING(NEO_DRIVE_MTR_CONFIGURE)
    m_motor->Configure(mtr_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING

    m_MaxSpeed = config.maxSpeed;
    m_correction_factor = config.correction_factor;
};

units::foot_t NeoDriveMotor::GetPosition()
{
    double position = (m_encoder->GetPosition())  / m_correction_factor;
    return units::foot_t{position};
}

void NeoDriveMotor::SetVelocity(units::velocity::feet_per_second_t v) {


    // TODO - return PID to not need a scaling factor to get to desired setpoint
    m_PID->SetReference(1.6666667 * v.to<double>(), rev::spark::SparkLowLevel::ControlType::kVelocity);

};


units::velocity::feet_per_second_t NeoDriveMotor::GetVelocity() {
    return  units::velocity::feet_per_second_t{m_encoder->GetVelocity()};

};



void NeoDriveMotor::SetIdleMode(bool m) {
    // TODO 2025 refactor makes doing this more challenging... have to figure out best way forward
    //m_motor->SetIdleMode(m ? rev::spark::SparkMax::IdleMode::kBrake : rev::spark::SparkMax::IdleMode::kCoast);
};


bool NeoDriveMotor::GetIdleMode() {
    return m_motor->configAccessor.GetIdleMode() == rev::spark::SparkBaseConfig::IdleMode::kBrake;
};



