#pragma once
#include "RobotControlData.h"
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <rev/SparkMax.h>
#include <rev/SparkAbsoluteEncoder.h>
#include <rev/SparkClosedLoopController.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/angle.h>
#include <units/acceleration.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>

class Climber
{
    public:
        Climber();
        ~Climber() = default; 
        double GetClimberSpeed();
        void SetClimberSpeed(double speed); 
        
    private:
        rev::spark::SparkMax m_climberMotor{4, rev::spark::SparkMax::MotorType::kBrushless}; //Change CAN ID!! 
        double m_climberSpeed;
        rev::spark::SparkClosedLoopController m_climberMotorPID = m_climberMotor.GetClosedLoopController();
        rev::spark::SparkAbsoluteEncoder m_climberMotorAbsEncoder = m_climberMotor.GetAbsoluteEncoder();
        double m_ProfileStartPos;                       
};