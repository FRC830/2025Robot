#include "HAL/AlgaeRemoverHAL.h"

AlgaeRemover::AlgaeRemover()
{
    ctre::phoenix6::configs::TalonFXConfiguration arm_config{};

    ctre::phoenix6::configs::Slot0Configs &slot0Configs = arm_config.Slot0
        .WithKP(ratbot::AlgaeRemoverConfig::Pivot::P)
        .WithKI(ratbot::AlgaeRemoverConfig::Pivot::I)
        .WithKD(ratbot::AlgaeRemoverConfig::Pivot::D);

    ctre::phoenix6::configs::FeedbackConfigs &arm_feedback_config = arm_config.Feedback
        .WithSensorToMechanismRatio(ratbot::AlgaeRemoverConfig::Pivot::POS_CONV_FACTOR);
    
    ctre::phoenix6::configs::MotorOutputConfigs &arm_output_config = arm_config.MotorOutput
        .WithInverted(ratbot::AlgaeRemoverConfig::Pivot::INVERTED)
        .WithNeutralMode(ratbot::AlgaeRemoverConfig::Pivot::IDLE_MODE);
    
    ctre::phoenix6::configs::CurrentLimitsConfigs &arm_currentlim_config = arm_config.CurrentLimits
        .WithSupplyCurrentLimit(ratbot::AlgaeRemoverConfig::Pivot::CURRENT_LIM)
        .WithSupplyCurrentLimitEnable(true);
        
    ctre::phoenix6::configs::VoltageConfigs &arm_voltage_config = arm_config.Voltage
        .WithPeakForwardVoltage(units::volt_t(ratbot::VOLTAGE_COMPENSATION))
        .WithPeakReverseVoltage(-units::volt_t(ratbot::VOLTAGE_COMPENSATION));

    arm_config
        .WithSlot0(slot0Configs)
        .WithFeedback(arm_feedback_config)
        .WithMotorOutput(arm_output_config)
        .WithCurrentLimits(arm_currentlim_config)
        .WithVoltage(arm_voltage_config);
        
    /* Retry config apply up to 5 times, report if failure */
    ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
    for (int i = 0; i < 5; ++i) {
        status = m_armMotor.GetConfigurator().Apply(arm_config);
        if (status.IsOK()) break;
    }
    if (!status.IsOK()) {
        std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
    }

    // Remover Config    
    rev::spark::SparkMaxConfig remover_config{};
    remover_config
        .Inverted(ratbot::AlgaeRemoverConfig::Remover::INVERTED)
        .SetIdleMode(ratbot::AlgaeRemoverConfig::Remover::IDLE_MODE)
        .SmartCurrentLimit(ratbot::AlgaeRemoverConfig::Remover::CURRENT_LIM)
        .VoltageCompensation(ratbot::VOLTAGE_COMPENSATION);
    remover_config.closedLoop.SetFeedbackSensor(rev::spark::ClosedLoopConfig::FeedbackSensor::kPrimaryEncoder);

    START_RETRYING(REMOVER_MOTOR_CONFIG)
    m_removerMotor.Configure(remover_config, rev::spark::SparkMax::ResetMode::kResetSafeParameters, rev::spark::SparkMax::PersistMode::kPersistParameters);
    END_RETRYING
}

double AlgaeRemover::GetPivotAngle()
{    
    return m_armMotor.GetPosition().GetValueAsDouble();
}

double AlgaeRemover::GetWheelSpeed()
{
     return m_armMotor.GetVelocity().GetValueAsDouble();
}

void AlgaeRemover::ProfiledMoveToAngle(double angle)
{
    if (std::fabs(angle - m_ProfileStartPos) > 0.0001)
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

    m_armMotor.SetPosition(units::angle::turn_t(angle/360.0 * 4096.0)); //documentation
}

void AlgaeRemover::SetRemoverSpeed(double speed)
{
    m_removerMotor.Set(speed);
}
