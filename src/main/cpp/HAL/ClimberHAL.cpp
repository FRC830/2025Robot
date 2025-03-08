#include "HAL/ClimberHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"

Climber::Climber()
{
    rev::spark::SparkMaxConfig climber_config{};
    climber_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    climber_config.closedLoop.Pidf(ratbot::ClimberConfig::P,ratbot::ClimberConfig::I,ratbot::ClimberConfig::D,ratbot::ClimberConfig::F);
    climber_config.encoder.VelocityConversionFactor(ratbot::ClimberConfig::VEL_CONV_FACTOR);
    climber_config.Inverted(ratbot::ClimberConfig::INVERTED);
    climber_config.SetIdleMode(ratbot::ClimberConfig::IDLE_MODE);
    climber_config.SmartCurrentLimit(ratbot::ClimberConfig::CURRENT_LIM);
    climber_config.VoltageCompensation(ratbot::VOLTAGE_COMPENSATION);

    START_RETRYING(CLIMBER_CONFIG)
    m_climberMotor.Configure(climber_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING    
}

void Climber::SetClimberSpeed(double speed)
{
    m_climberMotor.Set(speed);
}

double Climber::GetClimberPosition()
{
    return m_climberMotor.GetEncoder().GetPosition();
}
