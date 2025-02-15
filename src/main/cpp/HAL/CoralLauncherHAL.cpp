#include "HAL/CoralLauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"

CoralLauncher::CoralLauncher()
{
    rev::spark::SparkMaxConfig flywheel_config{};
    rev::spark::SparkMaxConfig indexer_config{};

    flywheel_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    flywheel_config.closedLoop.Pidf(ratbot::CoralLauncherConfig::Flywheel::P,ratbot::CoralLauncherConfig::Flywheel::I,ratbot::CoralLauncherConfig::Flywheel::D,ratbot::CoralLauncherConfig::Flywheel::F);
    flywheel_config.encoder.VelocityConversionFactor(ratbot::CoralLauncherConfig::Flywheel::VEL_CONV_FACTOR);
    flywheel_config.Inverted(ratbot::CoralLauncherConfig::Flywheel::INVERTED);
    flywheel_config.SetIdleMode(ratbot::CoralLauncherConfig::Flywheel::IDLE_MODE);
    flywheel_config.SmartCurrentLimit(ratbot::CoralLauncherConfig::Flywheel::CURRENT_LIM); 
    flywheel_config.VoltageCompensation(ratbot::VOLTAGE_COMPENSATION); 

    indexer_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    indexer_config.Inverted(ratbot::CoralLauncherConfig::Indexer::INVERTED);
    indexer_config.SetIdleMode(ratbot::CoralLauncherConfig::Indexer::IDLE_MODE);
    indexer_config.SmartCurrentLimit(ratbot::CoralLauncherConfig::Indexer::CURRENT_LIM);
    indexer_config.VoltageCompensation(ratbot::VOLTAGE_COMPENSATION);

    START_RETRYING(RIGHT_FLYWHEEL_CONFIG)
    m_rightMotor.Configure(flywheel_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING
    flywheel_config.Inverted(!ratbot::CoralLauncherConfig::Flywheel::INVERTED);
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