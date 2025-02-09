#include "HAL/CoralLauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"

CoralLauncher::CoralLauncher()
{
    //todo: implement CoralLauncher constructor
    rev::spark::SparkMaxConfig flywheel_config{};
    rev::spark::SparkMaxConfig indexer_config{};

    flywheel_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    flywheel_config.closedLoop.Pidf(0,0,0,0);
    flywheel_config.encoder.VelocityConversionFactor(0);
    flywheel_config.Inverted(false);
    flywheel_config.SetIdleMode(rev::spark::SparkMaxConfig::IdleMode::kCoast);
    flywheel_config.SmartCurrentLimit(0,0,0); 
    flywheel_config.VoltageCompensation(0); 

    indexer_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    indexer_config.Inverted(false);
    indexer_config.SetIdleMode(rev::spark::SparkMaxConfig::IdleMode::kCoast);
    indexer_config.SmartCurrentLimit(0,0,0);
    indexer_config.VoltageCompensation(0);

    START_RETRYING(RIGHT_FLYWHEEL_CONFIG)
    m_rightMotor.Configure(flywheel_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING
    START_RETRYING(LEFT_FLYWHEEL_CONFIG)
    m_leftMotor.Configure(flywheel_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING
    START_RETRYING(INDEXER_CONFIG)
    m_indexer.Configure(indexer_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING

}
void CoralLauncher::SetWheelSpeeds(double rightSpeed, double leftSpeed)
{
    m_desiredRightSpeed = rightSpeed;
    m_desiredLeftSpeed = leftSpeed;
    m_rightMotor.GetClosedLoopController().SetReference(rightSpeed, rev::spark::SparkLowLevel::ControlType::kVelocity);
    m_leftMotor.GetClosedLoopController().SetReference(leftSpeed, rev::spark::SparkLowLevel::ControlType::kVelocity);
}
void CoralLauncher::SetIndexerSpeed(double indexerSpeed)
{
    m_indexer.GetClosedLoopController().SetReference(indexerSpeed, rev::spark::SparkLowLevel::ControlType::kVelocity);
}
double CoralLauncher::GetRightWheelSpeed()
{
    return m_rightMotor.GetEncoder().GetVelocity();
}
double CoralLauncher::GetLeftWheelSpeed()
{
    return m_leftMotor.GetEncoder().GetVelocity();
}
bool CoralLauncher::AreFlywheelsAtDesiredSpeed()
{
    return ((abs(GetRightWheelSpeed() - m_desiredRightSpeed)<=SMALL_NUM)&&(abs(GetLeftWheelSpeed() - m_desiredLeftSpeed)<=SMALL_NUM));
}

bool CoralLauncher::BeamBreakStatus()
{
    //todo: implement beam break status code
    return m_beam_break.Get();
}