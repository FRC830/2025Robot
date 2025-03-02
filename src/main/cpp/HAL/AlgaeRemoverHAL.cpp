#include "HAL/AlgaeRemoverHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"

AlgaeRemover::AlgaeRemover()
{
    rev::spark::SparkMaxConfig pivot_config{};
    rev::spark::SparkMaxConfig remover_config{};

    pivot_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    pivot_config.closedLoop.Pidf(ratbot::AlgaeRemoverConfig::Pivot::P,ratbot::AlgaeRemoverConfig::Pivot::I,ratbot::AlgaeRemoverConfig::Pivot::D,ratbot::AlgaeRemoverConfig::Pivot::F);
    pivot_config.encoder.VelocityConversionFactor(ratbot::AlgaeRemoverConfig::Pivot::VEL_CONV_FACTOR);
    pivot_config.Inverted(ratbot::AlgaeRemoverConfig::Pivot::INVERTED);
    pivot_config.SetIdleMode(ratbot::AlgaeRemoverConfig::Pivot::IDLE_MODE);
    pivot_config.SmartCurrentLimit(ratbot::AlgaeRemoverConfig::Pivot::CURRENT_LIM); 
    pivot_config.VoltageCompensation(ratbot::VOLTAGE_COMPENSATION); 

    remover_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);
    remover_config.Inverted(ratbot::AlgaeRemoverConfig::Remover::INVERTED);
    remover_config.SetIdleMode(ratbot::AlgaeRemoverConfig::Remover::IDLE_MODE);
    remover_config.SmartCurrentLimit(ratbot::AlgaeRemoverConfig::Remover::CURRENT_LIM);
    remover_config.VoltageCompensation(ratbot::VOLTAGE_COMPENSATION);

    START_RETRYING(PIVOT_MOTOR_CONFIG)
    m_armMotor.Configure(pivot_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING

    START_RETRYING(REMOVER_MOTOR_CONFIG)
    m_removerMotor.Configure(remover_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING
}

double AlgaeRemover::GetPivotAngle()
{
    return m_ArmMotorAbsEncoder.GetPosition();
}

double AlgaeRemover::GetWheelSpeed()
{
    return m_armMotor.GetEncoder().GetVelocity();
}

void AlgaeRemover::ProfiledMoveToAngle(double angle)
{
    if (std::abs(angle - m_ProfileStartPos) > 0.0001)
    {
        m_algaeRemoverState = 0;
    }

    switch(m_algaeRemoverState)
    {
     case 0: 
        {
            m_ProfileStartPos = GetPivotAngle();

            m_Timer.Stop();
            m_Timer.Reset();
            m_Timer.Start();

            m_algaeRemoverState++;

            break;
        }

        case 1:
        {
            auto setPoint = m_Profile.Calculate(m_Timer.Get(),    
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_ProfileStartPos}, 0_deg_per_s},  
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{angle}, 0_deg_per_s}
            );

            SetAngle(setPoint.position.to<double>());

            if (m_Profile.IsFinished(m_Timer.Get())) {

                m_algaeRemoverState++;

            }



            break;
        }

        case 2: 
        {

            m_Timer.Stop();

            m_algaeRemoverState++;

            break;
        }

        
        default:
            break; 
    }
}

void AlgaeRemover::SetAngle(double angle)
{
    if (angle > ratbot::AlgaeRemoverConfig::Pivot::MAX_PIVOT_ANGLE)
    {
        angle = ratbot::AlgaeRemoverConfig::Pivot::MAX_PIVOT_ANGLE;
    }
    else if (angle < ratbot::AlgaeRemoverConfig::Pivot::MIN_PIVOT_ANGLE)
    {
        angle = ratbot::AlgaeRemoverConfig::Pivot::MIN_PIVOT_ANGLE;
    }

    m_armMotorPID.SetReference(angle, rev::spark::SparkMax::ControlType::kPosition);
}

void AlgaeRemover::SetRemoverSpeed(double speed)
{
    m_removerMotor.Set(speed);
}
