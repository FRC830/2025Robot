#include "HAL/AlgaeRemoverHAL.h"

void AlgaeRemover::SetPivotAngle(double angle)
{  
    
};
void AlgaeRemover::SetWheelSpeed(double speed)
{
    
};
double AlgaeRemover::GetPivotAngle()
{
    return pivotAngle;
};
double AlgaeRemover::GetWheelSpeed()
{
    return wheelSpeed;
};
void AlgaeRemover::ProfileMoveToAngle(double angle)
{
    switch(m_algaeRemoverState)
    {
     case 0: 
        {
            m_ProfileStartPos = GetAngle();

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

void AlgaeRemover::ResetAlgaeRemoverState()
{
    m_algaeRemoverState = 0;
}

double AlgaeRemover::GetAngle()
{
    return m_ArmMotorAbsEncoder.GetPosition();
}

void AlgaeRemover::SetRemoverSpeed(double speed)
{
    m_removerMotor.Set(speed);
}
