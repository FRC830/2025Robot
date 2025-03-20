#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"
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
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/core/CoreTalonFXS.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"

class AlgaeRemover
{
    public:
        AlgaeRemover(); 
        ~AlgaeRemover() = default;

        void MoveArm(double value);
        void ProfiledMoveToAngle(double angle);
        void SetRemoverSpeed(double speed);
        void ResetState();

        double GetPivotAngle();
        double GetWheelSpeed(); 

        void PivotAngleToTop();
        void PivotAngleToBottom();
        void PivotAngleToStow();

    private:
        void SetAngle(double angle);
        ctre::phoenix6::hardware::TalonFX m_armMotor{ALGAE_REMOVER_ARM_CAN_ID};
        rev::spark::SparkMax m_removerMotor{ALGAE_REMOVER_WHEEL_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        frc::Timer m_Timer = frc::Timer(); 
        int m_algaeRemoverState = 0;
        frc::TrapezoidProfile<units::degrees> m_Profile
        {
          frc::TrapezoidProfile<units::degrees>::Constraints{30_deg_per_s, 100_deg_per_s_sq}  
        };
        
        double m_ProfileStartPos;
};
