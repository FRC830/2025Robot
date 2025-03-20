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
    START_RETRYING(INDEXER1_CONFIG)
    m_indexer1.Configure(indexer_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING
    indexer_config.Inverted(!ratbot::CoralLauncherConfig::Indexer::INVERTED);
    START_RETRYING(INDEXER2_CONFIG)
    m_indexer2.Configure(indexer_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING

}
void CoralLauncher::SetWheelSpeeds(double rightSpeed, double leftSpeed)
{
    m_desiredRightSpeed = rightSpeed;
    m_desiredLeftSpeed = leftSpeed;

    // Don't use PID to go to 0 to avoid stripping belts
    auto rightControlType = (std::fabs(rightSpeed) <= 1.0f) ? rev::spark::SparkLowLevel::ControlType::kDutyCycle : rev::spark::SparkLowLevel::ControlType::kVelocity;
    auto leftControlType = (std::fabs(leftSpeed) <= 1.0f) ? rev::spark::SparkLowLevel::ControlType::kDutyCycle : rev::spark::SparkLowLevel::ControlType::kVelocity;

    m_rightMotor.GetClosedLoopController().SetReference(rightSpeed, rightControlType);
    m_leftMotor.GetClosedLoopController().SetReference(leftSpeed, leftControlType);
}
void CoralLauncher::SetIndexerSpeeds(double indexerSpeed)
{
    
    m_indexer1.GetClosedLoopController().SetReference(indexerSpeed, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
    m_indexer2.GetClosedLoopController().SetReference(indexerSpeed, rev::spark::SparkLowLevel::ControlType::kDutyCycle);
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
    return ((std::fabs(GetRightWheelSpeed() - m_desiredRightSpeed)<=SMALL_NUM)&&(std::fabs(GetLeftWheelSpeed() - m_desiredLeftSpeed)<=SMALL_NUM));
}

bool CoralLauncher::BeamBreakStatus()
{
    //todo: implement beam break status code
    return m_beam_break.Get();
}