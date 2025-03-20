#include "SmartPlanner.h"
#include <iostream>

SmartPlanner::SmartPlanner(PhotonVisionCamera &cam, WPISwerveDrive &swerve)
    : m_Cam(cam)
    , m_Swerve(swerve)
{}

void SmartPlanner::HandleInput(RobotControlData &data)
{
    if(data.plannerInput.Left_L1 || data.plannerInput.Left_L2 || data.plannerInput.Right_L1 || data.plannerInput.Right_L2)
    {
        SmartPlan(data);
    }
    else
    {
        m_state = 0;
        m_moveToPose.reset();
    }
}

#include <iostream>
void SmartPlanner::SmartPlan(RobotControlData &data)
{
    switch (m_state)
    {
        case 0:
        {
            std::cout << "case 0" << std::endl;
            //try reset odometry
            auto estimatedPose = m_Cam.GetPose();
            std::cout << estimatedPose.has_value() << std::endl;

            if (estimatedPose.has_value())
            {
                //std::cout << "estimated at: " << estimatedPose.value().estimatedPose.X().value() << ", " << estimatedPose.value().estimatedPose.Y().value() << std::endl; 
                m_tagId = m_Cam.GetAprilTagID();
                m_Swerve.UpdatePoseWithVision(estimatedPose.value().estimatedPose, estimatedPose.value().timestamp);
                m_state++;
            }
            break;
        }
        case 1:
        {
            std::cout << "case 1" << std::endl;
            //Get target pose
            enum ScoringLocation loc;
            if (data.plannerInput.Left_L1) {loc = ScoringLocation::L1_LEFT;}
            else if (data.plannerInput.Left_L2) {loc = ScoringLocation::L2_LEFT;}
            else if (data.plannerInput.Right_L1) {loc = ScoringLocation::L1_RIGHT;}
            else if (data.plannerInput.Right_L2) {loc = ScoringLocation::L2_RIGHT;}
            
            std::array<double,3> poseArray = m_positionMap.getPosition(m_tagId, loc);
            units::meter_t x{poseArray[0]};
            units::meter_t y{poseArray[1]};
            units::degree_t angle{poseArray[2]};
            frc::Rotation2d rot{angle};

            m_targetPose = frc::Pose2d{x, y, rot};

            //m_startPose = m_Swerve.GetPose();


            m_state++;
            break;
        }
        case 2:
        {
            std::cout << "case 2" << std::endl;
            // prespin flywheels
            if (data.plannerInput.Left_L1 || data.plannerInput.Right_L1)
            {
                data.coralInput.setFlywheelToL1Speed = true;
            }
            if(data.plannerInput.Left_L2 || data.plannerInput.Right_L2)
            {
                data.coralInput.setFlywheelToL2Speed = true;
            }

            // move to pose
            auto speeds = m_moveToPose.move(m_Swerve.GetPose(), m_targetPose);
            m_Swerve.Drive(speeds);
            if (m_moveToPose.isDone())
            {
                m_state++;
            }
            break;
        }
        case 3:
        {
            m_Swerve.Drive(0.0f, 0.0f, 0.0f);
            // if flywheels at speed run indexer
            if (data.coralOutput.flywheelsAtSpeed)
            {
                data.coralInput.indexerSpeeds = 1.0;
                if(!data.coralOutput.isBeamBroken)
                {
                    m_state++;
                }
            }
            break;
        }
        case 4:
        {
            //shut everything off
            data.coralInput.indexerSpeeds = 0.0;
            data.coralInput.setFlywheelToL1Speed = false;
            data.coralInput.setFlywheelToL2Speed = false;
            break;
        }
        default:
        {
            break;
        }
    }
}
