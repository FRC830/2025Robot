#include "MoveToPose.h"
#include "MechanismConfig.h"

// TODO: look at these files to understand how to setup and use a trapezoid move using switch statements
        // - https://github.com/FRC830/2024Robot/blob/master/src/main/include/subsystems/IntakeHAL.h (trapezoid move member variable init)
       //  - https://github.com/FRC830/2024Robot/blob/master/src/main/cpp/subsystems/IntakeHAL.cpp (ProfiledMoveToAngle function)
// TODO: don't worry about doing anything with the drive base for now

frc::ChassisSpeeds MoveToPose::move(frc::Pose2d current, frc::Pose2d desired) {
    switch(m_MoveToState){
        case 0:
        {
            m_MoveToState++;
            m_rotation = 0_deg_per_s;
            m_translation.first = 0_fps;
            m_translation.second = 0_fps;
            break;
        }
        case 1:
        {
            m_current = current;
            m_rotation = angularRotation(current.Rotation(), desired.Rotation());
            m_translation = linearTranslation(desired);
            break;
        }
        default:
        {
            break;
        }
    }
    return frc::ChassisSpeeds{m_translation.first, m_translation.second, m_rotation}; //vx, vy, omega
};

units::degrees_per_second_t MoveToPose::angularRotation(frc::Rotation2d current, frc::Rotation2d desired) {    
    /*
    "Efficient Rotation"
    double start = current.Degrees().value();
    double end = desired.Degrees().value();

    m_turn = end - start;
    if (m_turn > 180.0)
    {
        m_turn = m_turn - 360.0;
    }
    else if (m_turn < -180.0)
    {
        m_turn = m_turn + 360.0;
    }
    */
    auto error = desired-current;
    m_turn = error.Degrees().value();

    auto val = ((std::fabs(m_turn) / 180.0f) * ratbot::MoveToPoseConfig::MAX_TURN_SPEED_DEG_PER_SEC) + ratbot::MoveToPoseConfig::TURN_FEED_FORWARD_DEG_PER_SEC;
    
    if (m_turn < 0.0f)
    {
        val = -val;
    }


    if (std::fabs(m_turn) <= 2.0f)
    {
        static const double slow_turn_val = 10.0f;
        val = (m_turn > 0.0) ? -slow_turn_val : slow_turn_val;
        
        if (std::fabs(m_turn) <= 0.1f)
        {
            val = 0.0f;
            m_MoveAngleToState = 3;
        }
    }



    return units::angular_velocity::degrees_per_second_t{val};
    
    // switch (m_MoveAngleToState)
    // {
    //     case 0:
    //     {


            
    //         double start = m_current.Rotation().Degrees().value();
    //         double end = desired.Degrees().value();

    //         m_turn = end - start;
    //         if (m_turn > 180.0)
    //         {
    //             m_turn = m_turn - 360.0;
    //         }
    //         else if (m_turn < -180.0)
    //         {
    //             m_turn = m_turn + 360.0;
    //         }


    //         m_angularVelocity = 0_deg_per_s;
    //         m_timer.Restart();
    //         m_MoveAngleToState++;
    //         break;
    //     }
    //     case 1:
    //     {
    //         auto setPoint = m_Profile.Calculate(
    //             m_timer.Get(),
    //             frc::TrapezoidProfile<units::degrees>::State{units::degree_t{0.0f}, 0_deg_per_s},
    //             frc::TrapezoidProfile<units::degrees>::State{units::degree_t{m_turn}, 0_deg_per_s}    // insert the better end state here       
    //         );

    //         m_angularVelocity = setPoint.velocity;

    //         if (m_Profile.IsFinished(m_timer.Get())) {
    //             m_MoveAngleToState++;
    //         }

    //         break;
    //     }
    //     case 2:
    //     {
    //         m_timer.Stop();
    //         m_MoveAngleToState++;
    //         break;
    //     }
    //     default:
    //     {
    //         break;
    //     }
    // }
    // return m_angularVelocity;
};

std::pair<units::feet_per_second_t, units::feet_per_second_t> MoveToPose::linearTranslation(frc::Pose2d desired) {
    // double distance = sqrt(pow((double)desired.X() - current.X(), 2.0) + pow(0.0 + desired.Y() - current.Y(), 2.0));
    double desiredx = desired.X().value();
    double currentx = m_current.X().value();
    double desiredy = desired.Y().value();
    double currenty = m_current.Y().value();

    m_vx = 0;
    m_vy = 0;
    
    double x = (desiredx - currentx) * (desiredx - currentx);
    double y = (desiredy - currenty) * (desiredy - currenty);
    
    m_distance = sqrt(x + y);
    std::cout << "distance: " << m_distance << std::endl;
    double theta =  atan2(desiredy-currenty ,  desiredx - currentx);

    m_vxCoeff = cos(theta);
    m_vyCoeff = sin(theta);

    auto val = ((std::fabs(m_distance) / 2.0f) * ratbot::MoveToPoseConfig::MAX_SPEED_M_PER_SEC) + ratbot::MoveToPoseConfig::SPEED_FEED_FORWARD_M_PER_SEC;

    //m_distance = -m_distance;

    if (std::fabs(m_distance) <= 0.08f)
    {
        val = 0.0f;
    }

    auto vx = units::meters_per_second_t{val*m_vxCoeff};
    auto vy = units::meters_per_second_t{val*m_vyCoeff};


    std::pair<units::feet_per_second_t, units::feet_per_second_t> velocity = {vx, vy};
    //std::pair<units::meters_per_second_t, units::meters_per_second_t> velocity = {units::meters_per_second_t{0.0f}, units::meters_per_second_t{0.0f}};
    return velocity; //pair of vx and vy
    
    // switch (m_MoveTranslationToState)
    // {
    // case 0:
    // {
        
    //     double desiredx = desired.X().value();
    //     double currentx = m_current.X().value();
    //     double desiredy = desired.Y().value();
    //     double currenty = m_current.Y().value();

    //     m_vx = 0;
    //     m_vy = 0;
        
    //     double x = (desiredx - currentx) * (desiredx - currentx);
    //     double y = (desiredy - currenty) * (desiredy - currenty);
        
    //     m_distance = sqrt(x + y);
    //     double theta =  -atan2(desiredy - currenty, desiredx - currentx);
    //     m_vxCoeff = cos(theta);
    //     m_vyCoeff = sin(theta);

    //     m_timerLin.Restart();
    //     m_MoveTranslationToState++;
    //     // FIXME: switch statement fall-through, is this intentional?
    // }
    // case 1:
    // {
    //     auto setDistance = m_ProfileLin.Calculate(
    //         m_timerLin.Get(),
    //         frc::TrapezoidProfile<units::foot>::State{units::foot_t{0.0f}, 0_fps},
    //         frc::TrapezoidProfile<units::foot>::State{units::foot_t{m_distance}, 0_fps}       
    //     );


    //     m_vx = -setDistance.velocity.to<double>() * m_vxCoeff;
    //     m_vy = -setDistance.velocity.to<double>() * m_vyCoeff;

    //     // make the robot move with vx vy


    //     if (m_ProfileLin.IsFinished(m_timerLin.Get())) {
    //             m_MoveTranslationToState++;
    //         }

    //     break;
    // }
    // case 2:
    // {
    //     m_timerLin.Stop();
    //     m_MoveTranslationToState++;
    //     break;
    // }
    // default:
    //     break;
    // }
    
};

void MoveToPose::reset()
{

    m_MoveAngleToState = 0;
    m_MoveTranslationToState = 0;
    m_MoveToState = 0;
}

bool MoveToPose::isDone()
{
    return ( m_MoveTranslationToState > 2);
}

bool MoveToPose::turnIsDone()
{
    return m_MoveAngleToState == 3;
}