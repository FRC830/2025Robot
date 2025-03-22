#include "HAL/AlgaeRemoverHAL.h"

AlgaeRemover::AlgaeRemover()
{
    ctre::phoenix6::configs::TalonFXConfiguration arm_config{};

    ctre::phoenix6::configs::Slot0Configs &slot0Configs = arm_config.Slot0
        .WithKP(ratbot::AlgaeRemoverConfig::Pivot::P)
        .WithKI(ratbot::AlgaeRemoverConfig::Pivot::I)
        .WithKD(ratbot::AlgaeRemoverConfig::Pivot::D)
        .WithKG(ratbot::AlgaeRemoverConfig::Pivot::F);
    ctre::phoenix6::configs::MotorOutputConfigs &arm_output_config = arm_config.MotorOutput
        .WithInverted(ratbot::AlgaeRemoverConfig::Pivot::INVERTED)
        .WithNeutralMode(ratbot::AlgaeRemoverConfig::Pivot::IDLE_MODE);
    
    arm_config
        .WithSlot0(slot0Configs)
        .WithMotorOutput(arm_output_config);
        
    /* Retry config apply up to 5 times, report if failure */
    ctre::phoenix::StatusCode status = ctre::phoenix::StatusCode::StatusCodeNotInitialized;
    for (int i = 0; i < 5; ++i) {
        status = m_armMotor.GetConfigurator().Apply(arm_config);
        if (status.IsOK()) break;
    }
    if (!status.IsOK()) {
        //std::cout << "Could not apply configs, error code: " << status.GetName() << std::endl;
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

#include <iostream>

double AlgaeRemover::GetPivotAngle()
{    
    return m_armMotor.GetPosition().GetValueAsDouble();
}

void AlgaeRemover::PivotAngleToTop(){
    if (AlgaeRemover::GetPivotAngle() < ratbot::AlgaeRemoverConfig::Pivot::TOP_REMOVER_POS)
    {
        AlgaeRemover::MoveArm(1.0);
    }
    else if(AlgaeRemover::GetPivotAngle() > ratbot::AlgaeRemoverConfig::Pivot::TOP_REMOVER_POS)
    {
        AlgaeRemover::MoveArm(-1.0);
    }else
    {
        AlgaeRemover::MoveArm(0.0);
    }
}
void AlgaeRemover::PivotAngleToBottom(){
    if (AlgaeRemover::GetPivotAngle() < ratbot::AlgaeRemoverConfig::Pivot::BOTTOM_REMOVER_POS)
    {
        AlgaeRemover::MoveArm(1.0);
    }
    else if(AlgaeRemover::GetPivotAngle() > ratbot::AlgaeRemoverConfig::Pivot::BOTTOM_REMOVER_POS)
    {
        AlgaeRemover::MoveArm(-1.0);
    }else
    {
        AlgaeRemover::MoveArm(0.0);
    }
}
void AlgaeRemover::PivotAngleToStow(){
    if (AlgaeRemover::GetPivotAngle() < ratbot::AlgaeRemoverConfig::Pivot::STOW_REMOVER_POS)
    {
        AlgaeRemover::MoveArm(0.0);
    }
    else if(AlgaeRemover::GetPivotAngle() > ratbot::AlgaeRemoverConfig::Pivot::STOW_REMOVER_POS)
    {
        AlgaeRemover::MoveArm(-1.0);
    }else
    {
        AlgaeRemover::MoveArm(0.0);
    }
}
void AlgaeRemover::MoveArm(double value) {
    // std::cout << GetPivotAngle() << std::endl;

    if (value == 1.0  && (GetPivotAngle() <= 8.28))
    {
        m_armMotor.Set(0.05);
       // std::cout << "set going up" << std::endl;
    }
    else if ((value == -1.0) && (GetPivotAngle() >= -0.301)) 
    {
        m_armMotor.Set(-0.05);


       // std::cout << "set going down" << std::endl;
    } else 
    {
        m_armMotor.Set(0.0);
       // std::cout << "stop" << std::endl;
    }
}

double AlgaeRemover::GetWheelSpeed()
{
     return m_armMotor.GetVelocity().GetValueAsDouble();
}
#include <iostream>

void AlgaeRemover::ProfiledMoveToAngle(double angle)
{
    if (std::fabs(angle - m_ProfileStartPos) < 0.0001)
    {
        m_algaeRemoverState = 0;
    }

    switch(m_algaeRemoverState)
    {
     case 0: 
        {
           // std::cout << "case 0" << std::endl;
            m_ProfileStartPos = GetPivotAngle();

            m_Timer.Stop();
            m_Timer.Reset();
            m_Timer.Start();

            m_algaeRemoverState++;
           // std::cout << m_algaeRemoverState << std::endl;
            break;
        }
        case 1:
        {
           // std::cout << "case 1" << std::endl;
            auto setPoint = m_Profile.Calculate(m_Timer.Get(),    
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_ProfileStartPos}, 0_deg_per_s},  
            frc::TrapezoidProfile<units::degrees>::State{units::degree_t{angle}, 0_deg_per_s}
            );
           // std::cout << "got to setangle" << std::endl;

            SetAngle(setPoint.position.to<double>());

            if (m_Profile.IsFinished(m_Timer.Get())) {

                m_algaeRemoverState++;

            }



            break;
        }
        case 2: 
        {

           // std::cout << "case 2" << std::endl;
            m_Timer.Stop();

            m_algaeRemoverState++;

            break;
        }
        default:
            break; 
    }
    //std::cout << "got thru profiled move" << std::endl;

}

void AlgaeRemover::SetAngle(double angle)
{
    //std::cout << "got inside setangle" << std::endl;
    if (angle > ratbot::AlgaeRemoverConfig::Pivot::MAX_PIVOT_ANGLE)
    {
        angle = ratbot::AlgaeRemoverConfig::Pivot::MAX_PIVOT_ANGLE;
    }
    else if (angle < ratbot::AlgaeRemoverConfig::Pivot::MIN_PIVOT_ANGLE)
    {
        angle = ratbot::AlgaeRemoverConfig::Pivot::MIN_PIVOT_ANGLE;
    }
   // std::cout << angle/360.0 * 4096.0 << std::endl;

    m_armMotor.SetPosition(units::angle::turn_t(angle/360.0 * 4096.0)); //documentation
}

void AlgaeRemover::SetRemoverSpeed(double speed)
{
    m_removerMotor.Set(speed);
}

void AlgaeRemover::ResetState()
{
    m_algaeRemoverState = 0;
}