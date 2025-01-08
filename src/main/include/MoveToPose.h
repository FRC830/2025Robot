// TODO: what do all header files NEED to start with?

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

        // Uses swerve odometry to generate the 'initial' pose
        void move(frc::Pose2d desired);

        // TODO: all functions below should be private

        // Moves robot from initial to desired
        void move(frc::Pose2d initial,frc::Pose2d desired);
        
        // Trapezoid move to handle angular rotation to desired pose
        double angularRotation(frc::Pose2d desired, frc::Pose2d current);
        
        // Trapezoid move to handle linear translation to desired pose
        frc::Pose2d linearTranslation(frc::Pose2d initial,frc::Pose2d desired);

        // TODO: create helper functions as needed
         
};