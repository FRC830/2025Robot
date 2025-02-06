#pragma once

#include "RobotControlData.h"
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include "rev/SparkAbsoluteEncoder.h"
#include "rev/SparkClosedLoopController.h"
#include <frc/Timer.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/angle.h>
#include <units/acceleration.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

class AlgaeRemover
{
    public:
        AlgaeRemover() = default;
        ~AlgaeRemover() = default;
        void SetPivotAngle(double angle);
        void SetWheelSpeed(double speed);
        double GetPivotAngle();
        double GetWheelSpeed(); 
        void ProfileMoveToAngle(double angle);
        void SetRemoverSpeed(double speed);
        void ResetAlgaeRemoverState();
        void SetAngle(double angle);
        double GetAngle();
    private:
        double pivotAngle = 0.0;
        double wheelSpeed = 0.0;
        double pullingWheelSpeed;
        rev::spark::SparkMax m_armMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_removerMotor{0, rev::spark::SparkMax::MotorType::kBrushless};
        double m_removerSpeed;
        frc::Timer m_Timer = frc::Timer(); 
        int m_algaeRemoverState = 0;
        frc::TrapezoidProfile<units::degrees> m_Profile
        {
          frc::TrapezoidProfile<units::degrees>::Constraints{30_deg_per_s, 100_deg_per_s_sq}  
        };
        
        rev::spark::SparkClosedLoopController m_armMotorPID= m_armMotor.GetClosedLoopController();
        rev::spark::SparkAbsoluteEncoder m_ArmMotorAbsEncoder= m_armMotor.GetAbsoluteEncoder();
        double m_ProfileStartPos;

        double MAX_PIVOT_ANGLE = 90.0;
        double MIN_PIVOT_ANGLE = 0.0;
};