#include "HAL/AlgaeRemoverHAL.h"

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
    if (angle > MAX_PIVOT_ANGLE)
    {
        angle = MAX_PIVOT_ANGLE;
    }
    else if (angle < MIN_PIVOT_ANGLE)
    {
        angle = MIN_PIVOT_ANGLE;
    }

    m_armMotorPID.SetReference(angle, rev::spark::SparkMax::ControlType::kPosition);
}

void AlgaeRemover::SetRemoverSpeed(double speed)
{
    m_removerMotor.Set(speed);
}
