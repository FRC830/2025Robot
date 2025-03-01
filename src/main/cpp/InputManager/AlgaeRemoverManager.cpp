/*


#include "InputManager/AlgaeRemoverManager.h"

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
            // m_Timer.Restart();

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
*/