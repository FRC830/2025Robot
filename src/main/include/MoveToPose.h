#include <frc/geometry/Pose2d.h>
#include <cmath>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/Timer.h>


class MoveToPose
{
    private:
        frc::TrapezoidProfile<units::degrees> m_Profile{
            frc::TrapezoidProfile<units::degrees>::Constraints{180_deg_per_s, 90_deg_per_s_sq}   
        };

        int m_MoveToState = 0;
        frc::Timer m_timer; 
    
    public:
        MoveToPose() = default;
        ~MoveToPose() = default;

        // TODO: Create a top level function that takes in a SINGLE frc::Pose2d called 'desired'
        void move(frc::Pose2d desired);
        // TODO: create a function that takes a TWO frc::Pose2d called 'initial' and 'desired'
        //       - this function gets called by the first one and we will use swerve odometry to generate the 'initial'
        //       - this function will call two functions to handle the linear translation, and the angular rotation of the drive base
        void move(frc::Pose2d initial,frc::Pose2d desired);
        // TODO: create a function to handle the angular translation of the drivebase (this will implement a trapezoid move)
        //       - should return the desired degrees_per_second_t the drive base should rotate by
        double angularRotation(frc::Pose2d desired, frc::Pose2d current);
        // TODO: create a function to handle the linear translation of the drivebase (this will implement a trapezoid move)
        //       - this uses the math we did using the distance formula and then splitting it up into th vx and vy component
        //       - should return vx and vy as feet_per_second_t
        frc::Pose2d linearTranslation(frc::Pose2d initial,frc::Pose2d desired);
        // TODO: create helper functions as needed
         
};