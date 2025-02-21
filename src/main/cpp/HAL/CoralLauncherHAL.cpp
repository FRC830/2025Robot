#include "HAL/CoralLauncherHAL.h"
/**/
void CoralLauncher::L1Launch()
{
    switch(m_l1LaunchState)
    {
        case 0:
        {
            m_Timer.Stop();
            m_Timer.Reset();
            m_Timer.Start();

            m_l1LaunchState++;
            break;
        }

        case 1:
        {
            if(!m_beam_break.Get())
            {
                m_l1LaunchState++;
                break;
            }
            SetIndexerSpeed(1.0);
        }

        case 2:
        {
            SetIndexerSpeed(0);
            m_l1LaunchState++;
            break;
        }
        
        case 3:
        {
            if(m_beam_break.Get()) 
            {
                m_l1LaunchState++;
                break;
            }
            SetRightWheelSpeed(-m_l1LaunchSpeed);
            SetLeftWheelSpeed(m_l1LaunchSpeed);
        }

        case 4:
        {
            SetRightWheelSpeed(0);
            SetLeftWheelSpeed(0);
            break;
        }

        default:
        {
            SetLeftWheelSpeed(0);
            SetRightWheelSpeed(0);
            SetIndexerSpeed(0);
            break;
        }
    }
}
void CoralLauncher::L2Launch()
{
    switch(m_l2LaunchState)
    {
        case 0:
        {
            m_Timer.Stop();
            m_Timer.Reset();
            m_Timer.Start();

            m_l2LaunchState++;
            break;
        }

        case 1:
        {
            if(!m_beam_break.Get())
            {
                m_l2LaunchState++;
                break;
            }
            SetIndexerSpeed(1.0);
        }

        case 2:
        {
            SetIndexerSpeed(0);
            m_l2LaunchState++;
            break;
        }

        case 3:
        {
            if(m_beam_break.Get())
            {
                m_l2LaunchState++;
                break;
            }
            SetRightWheelSpeed(m_l2LaunchSpeed);
            SetLeftWheelSpeed(m_l2LaunchSpeed);
        }

        case 4:
        {
            SetRightWheelSpeed(0);
            SetLeftWheelSpeed(0);
            break;
        }

        default:
        {
            SetLeftWheelSpeed(0);
            SetRightWheelSpeed(0);
            SetIndexerSpeed(0);
            break;
        }
    }
}

//void CoralLauncher::IndexerLaunch()
// {
//     switch(m_indexerState)
//     {
//         case 0:
//         {
//             m_Timer.Stop();
//             m_Timer.Reset();
//             m_Timer.Start();

//             m_indexerState++;
//             break;
//         }

//         case 1:
//         {
//             if(!m_beam_break.Get())
//             {
//                 m_indexerState++;
//                 break;
//             }
//             SetIndexerSpeed(1.0);
//         }

//         case 2:
//         {
//             SetIndexerSpeed(0);
//             break;
//         }
//     }
// }

void CoralLauncher::SetRightWheelSpeed(double speed)
{
    // todo
    m_RightWheelSpeed = speed;
    rightMotor.Set(m_RightWheelSpeed);
}
void CoralLauncher::SetLeftWheelSpeed(double speed)
{
    // todo
    m_LeftWheelSpeed = speed;
    leftMotor.Set(m_LeftWheelSpeed);
}
void CoralLauncher::SetIndexerSpeed(double speed)
{
    //todo idk what indexer is check CAD
    indexerSpeed = speed;
    indexer.Set(indexerSpeed);

}
double CoralLauncher::GetRightWheelSpeed()
{
    return m_RightWheelSpeed;
}
double CoralLauncher::GetLeftWheelSpeed()
{
    return m_LeftWheelSpeed;
}

void CoralLauncher::ResetL1LaunchState()
{
    m_l1LaunchState = 0;
}

void CoralLauncher::ResetL2LaunchState()
{
    m_l2LaunchState = 0;
}