#include "InputManager/CoralLauncherManager.h"

void CoralLauncherManager::L1Launch()
{
    switch(m_l1LaunchState)
    {
        case 0:
        {
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
            m_CoralLauncher.SetIndexerSpeed(1.0);
            break;
        }

        case 2:
        {
            m_CoralLauncher.SetIndexerSpeed(0);
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
            m_CoralLauncher.SetWheelSpeeds(-m_l1LaunchSpeed*multiplier, m_l1LaunchSpeed); //shouldn't one launch speed be more than the other? to turn the coral
        }

        case 4:
        {
            m_CoralLauncher.SetWheelSpeeds(0, 0);
            break;
        }
    }
}

void CoralLauncherManager::L2Launch()
{
    switch(m_l2LaunchState)
    {
        case 0:
        {
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
            m_CoralLauncher.SetIndexerSpeed(1.0);
            break;
        }

        case 2:
        {
            m_CoralLauncher.SetIndexerSpeed(0);
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
            m_CoralLauncher.SetWheelSpeeds(-m_l2LaunchSpeed, m_l2LaunchSpeed);
        }

        case 4:
        {
            m_CoralLauncher.SetWheelSpeeds(0, 0);
            break;
        }
    }
}

//void CoralLauncherManager::IndexerLaunch()
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

void CoralLauncherManager::ResetStates(bool resetL1, bool resetL2, bool resetIndexer)
{
    if(resetL1)
    {
        m_l1LaunchState = 0;
    }
    if(resetL2)
    {
        m_l2LaunchState = 0;
    }
    if(resetIndexer)
    {
        m_indexerState = 0;
    }
}