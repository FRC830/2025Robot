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
        m_pathstate = 0;
        //m_Swerve.SetFieldOriented();
    }
}

#include <iostream>
void SmartPlanner::SmartPlan(RobotControlData &data)
{
    if (data.plannerInput.Left_L1 || data.plannerInput.Right_L1)
    {
        data.coralInput.setFlywheelToL1Speed = true;
    }
    if(data.plannerInput.Left_L2 || data.plannerInput.Right_L2)
    {
        data.coralInput.setFlywheelToL2Speed = true;
    }
    switch (m_state)
    {
        case 0:
        {
            m_Swerve.SetRobotOriented();
            //try reset odometry
            auto estimatedPose = m_Cam.GetPose();
            std::cout << estimatedPose.has_value() << std::endl;

            if (estimatedPose.has_value())
            {
                std::cout << "estimated at: " << estimatedPose.value().estimatedPose.X().value() << ", " << estimatedPose.value().estimatedPose.Y().value() << std::endl; 
                m_tagId = m_Cam.GetAprilTagID();
                std::cout << "tag id: " << m_tagId << std::endl;
                m_Swerve.UpdatePoseWithVision(estimatedPose.value().estimatedPose, estimatedPose.value().timestamp);
                m_state++;
            }
            break;
        }
        case 1:
        {
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

            m_startPose = m_Swerve.GetPose();


            m_state++;
            break;
        }
        case 2:
        {
            // prespin flywheels
            

            // only turn
            auto speeds = m_moveToPose.move(m_Swerve.GetPose(), m_targetPose);
            m_Swerve.Drive(0.0f, 0.0f, speeds.omega);
            if (m_moveToPose.turnIsDone())
            {
                m_path = std::make_unique<frc2::CommandPtr>(pathplanner::AutoBuilder::pathfindToPose(m_targetPose, m_constraints, 0.0_mps));
                m_state++;
            }
            //m_Swerve.Drive(speeds.vx, speeds.vy, 0);
            break;
        }
        case 3:
        {
            followPath();

            if (m_pathstate > 2)
            {
                m_state++;
            }

            break;
        }
        case 4:
        {
            std::cout << "Smartplanning DONE! -- Alex Liu" << std::endl;
            m_Swerve.Drive(0.0f, 0.0f, 0.0f);
            // if flywheels at speed run indexer
            if (data.coralOutput.flywheelsAtSpeed)
            {
              data.coralInput.indexerSpeeds = 1.0;
              m_state++;  
            }
            break;
        }
        case 5:
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

void SmartPlanner::followPath()
{
    switch(m_pathstate)
  {
    case 0:
      {
        m_path->get()->Initialize();
        m_pathstate++;
      }
      break;
    case 1:
      {
        m_path->get()->Execute();
        if (m_path->get()->IsFinished())
        {
          m_pathstate++;
        }
      }
      break;
    case 2:
      {
        m_path->get()->End(false);
        m_pathstate++;
      }
      break;
    case 3:
      {
        m_Swerve.Drive(0.0, 0.0, 0.0);
      }
    
      break;
    default:
      break;
  }
}
