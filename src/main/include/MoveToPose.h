#pragma once

#include <frc/geometry/Pose2d.h>
#include <cmath>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/Timer.h>

#include <units/voltage.h>
#include <units/angle.h>
//#include <units/acceleration.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
//#include <units/math.h>


class MoveToPose
{
    private:
        frc::TrapezoidProfile<units::degrees> m_Profile{
            frc::TrapezoidProfile<units::degrees>::Constraints{180_deg_per_s, 90_deg_per_s_sq}   
        };
        int m_MoveAngleToState = 0;
        int m_MoveToState = 0;
        frc::Timer m_timer;

        // Moves robot from initial to desired
        void move(frc::Pose2d current,frc::Pose2d desired);
        
        // Trapezoid move to handle angular rotation to desired pose
        void angularRotation(frc::Rotation2d current, frc::Rotation2d desired);
        
        // Trapezoid move to handle linear translation to desired pose
        double linearTranslation(frc::Pose2d current,frc::Pose2d desired);

    public:
        MoveToPose() = default;
        ~MoveToPose() = default;

        // Uses swerve odometry to generate the 'initial' pose
        void move(frc::Pose2d desired);

        // TODO: all functions below should be private
        //       all functions should have (current, desired)... instead of (initial, desired) or (desired, current)

        // Moves robot from initial to desired
        void move(frc::Pose2d initial,frc::Pose2d desired);
        
        // TODO: create helper functions as needed
         
};