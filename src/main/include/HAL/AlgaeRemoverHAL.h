#pragma once

#include "RobotControlData.h"
#include <rev/SparkMax.h>
#include <rev/SparkAbsoluteEncoder.h>
#include <rev/SparkClosedLoopController.h>
#include <frc/Timer.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/angle.h>
#include <units/acceleration.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <frc/smartdashboard/SmartDashboard.h>

class AlgaeRemover
{
    public:
        AlgaeRemover();
        ~AlgaeRemover() = default;

        void ProfiledMoveToAngle(double angle);
        void SetRemoverSpeed(double speed);

        double GetPivotAngle();
        double GetWheelSpeed(); 

    private:
        void SetAngle(double angle);

        rev::spark::SparkMax m_armMotor{40, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_removerMotor{41, rev::spark::SparkMax::MotorType::kBrushless};
        double m_removerSpeed;
        frc::Timer m_Timer = frc::Timer(); 
        int m_algaeRemoverState = 0;
        frc::TrapezoidProfile<units::degrees> m_Profile
        {
          frc::TrapezoidProfile<units::degrees>::Constraints{30_deg_per_s, 100_deg_per_s_sq}  
        };
        
        rev::spark::SparkClosedLoopController m_armMotorPID = m_armMotor.GetClosedLoopController();
        rev::spark::SparkAbsoluteEncoder m_ArmMotorAbsEncoder = m_armMotor.GetAbsoluteEncoder();
        double m_ProfileStartPos;
};