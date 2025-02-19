#include"ratpack/swerve/NeoTurnMotor.h"
#include "ratpack/SparkMaxDebugMacro.h"
#include <rev/config/SparkMaxConfig.h>

void NeoTurnMotor::Configure(SwerveTurnMotorConfig &config){
    m_pastCommandAngle = -1000000.0;
    m_AbsouluteEncoder = config.absouluteEncoder;
    m_turn_motor = config.turn_motor;
    m_relative_Encoder = config.relative_Encoder;
    m_PID = config.PID;

    rev::spark::SparkMaxConfig mtr_config{};
    mtr_config.SetIdleMode(rev::spark::SparkMaxConfig::IdleMode::kBrake);

    mtr_config.encoder.PositionConversionFactor(config.ratio);

    mtr_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    mtr_config.closedLoop.Pidf(config.p, config.i, config.d, config.ff);

    mtr_config.SmartCurrentLimit(config.turn_motor_current_limit);

    mtr_config.VoltageCompensation(config.swerve_voltage_compensation);

    mtr_config.Inverted(config.inverted);

    START_RETRYING(NEO_TURN_MTR_CONFIGURE)
    m_turn_motor->Configure(mtr_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING
};    

void NeoTurnMotor::SetRotation(frc::Rotation2d deg){
    if (std::abs(m_pastCommandAngle-deg.Degrees().to<double>()) > 0.000001)
    {
        frc::Rotation2d realTurn = deg - GetRotation();
        if(realTurn.Degrees().to<double>() > 180.0) {

            realTurn = realTurn - frc::Rotation2d(units::degree_t(360.0));

        } else if (realTurn.Degrees().to<double>() < -180.0) {

            realTurn = realTurn + frc::Rotation2d(units::degree_t(360.0));

        }
    
        double targetPos = m_relative_Encoder->GetPosition() + realTurn.Degrees().to<double>();
        m_PID->SetReference(targetPos, rev::spark::SparkLowLevel::ControlType::kPosition);
        m_pastCommandAngle = deg.Degrees().to<double>();
    }
}; 

frc::Rotation2d NeoTurnMotor::GetRotation(){
    return m_AbsouluteEncoder->GetHeading();
}; 

bool NeoTurnMotor::GetInverted(){
    return m_turn_motor->GetInverted(); // FIXME: Deprecated
}; 
void NeoTurnMotor::SetInverted(bool invert){
    m_turn_motor->SetInverted(invert); // FIXME: Deprecated
}; 
void NeoTurnMotor::ForceTurnDirectionCW(){
};
void NeoTurnMotor::ForceTurnDirectionCCW(){
};

//12.8:1
//537.6 
