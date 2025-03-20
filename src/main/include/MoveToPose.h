#pragma once

#include <frc/geometry/Pose2d.h>
#include <cmath>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/Timer.h>
#include <frc/kinematics/ChassisSpeeds.h>

#include <units/voltage.h>
#include <units/angle.h>
#include <units/base.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/acceleration.h>
//#include <units/math.h>


class MoveToPose
{
    private:
        frc::TrapezoidProfile<units::degrees> m_Profile{
            frc::TrapezoidProfile<units::degrees>::Constraints{180_deg_per_s, 90_deg_per_s_sq}   
        };
        frc::TrapezoidProfile<units::foot> m_ProfileLin{
            frc::TrapezoidProfile<units::foot>::Constraints{3_fps, 0.25_fps_sq}   
        };  
        int m_MoveAngleToState = 0;
        int m_MoveTranslationToState = 0;
        int m_MoveToState = 0;
        frc::Timer m_timer;
        frc::Pose2d m_current;
        frc::Timer m_timerLin;
        double m_turn;
        double m_distance;
        double m_vxCoeff;
        double m_vyCoeff;
        double m_vx;
        double m_vy;
        units::degrees_per_second_t m_angularVelocity;
        units::degrees_per_second_t m_rotation;
        std::pair<units::feet_per_second_t, units::feet_per_second_t> m_translation;
        
        // Trapezoid move to handle angular rotation to desired pose
        units::degrees_per_second_t angularRotation(frc::Rotation2d current, frc::Rotation2d desired);
        
        // Trapezoid move to handle linear translation to desired pose
        std::pair<units::feet_per_second_t, units::feet_per_second_t> linearTranslation(frc::Pose2d desired);


    public:
        MoveToPose() = default;
        ~MoveToPose() = default;

        // Uses swerve odometry to generate the 'initial' pose
        frc::ChassisSpeeds move(frc::Pose2d current, frc::Pose2d desired);
        void reset();
        bool isDone();

        bool turnIsDone();

        // TODO: all functions below should be private
        //       all functions should have (current, desired)... instead of (initial, desired) or (desired, current)

        // Moves robot from initial to desired
        
        // TODO: create helper functions as needed
         
};