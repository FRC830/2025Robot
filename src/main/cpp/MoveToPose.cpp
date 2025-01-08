// TODO: classes we define should have "" instead of <> for their include statement
#include <MoveToPose.h>

// TODO: look at these files to understand how to setup and use a trapezoid move using switch statements
         - https://github.com/FRC830/2024Robot/blob/master/src/main/include/subsystems/IntakeHAL.h (trapezoid move member variable init)
         - https://github.com/FRC830/2024Robot/blob/master/src/main/cpp/subsystems/IntakeHAL.cpp (ProfiledMoveToAngle function)
// TODO: don't worry about doing anything with the drive base for now

void MoveToPose::move(frc::Pose2d desired) {
    // TODO: this should be in a switch statement:
    //       - case 0: query swerve for current position and save to member variable
    //       - case 1: call move(current, desired)
     // TODO: query swerve drive for current pose
     frc::Pose2d current = frc::Pose2d(0, 0, frc::Rotation2d(0));
     move(current, desired);
};

void MoveToPose::move(frc::Pose2d desired, frc::Pose2d current) {
    angularRotation(desired.getRotation(), current.getRotation());
    linearTranslatinon(current, desired);   
};

double MoveToPose::angularRotation(frc::Pose2d desired, frc::Pose2d current) {
    switch (m_MoveToState)
    {
    case 0:
        m_timer.Restart();
        // todo get the angle
        m_MoveToState++;
        break;
    case 1:
        m_Profile.Calculate(
            m_timer.Get(),
            frc::TrapezoidProfile<units::degrees>::State{desired, 0},
            frc::TrapezoidProfile<units::degrees>::State{current, 0}           
        );

        // todo set a variable for line 35 and rotate the robot

        if (m_Profile.IsFinished(m_timer.Get())) {
            m_MoveToState++;
        }

        break;
    
    case 2:
        m_timer.Stop();
        m_MoveToState++;
        break;

    default:
        break;
    }
};

double linearTranslatinon(frc::Pose2d initial,frc::Pose2d desired) {
    double distance=sqrt(pow(desired.x-initial.x,2)+pow(desired.y-initial.y,2))
};
