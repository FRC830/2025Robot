#pragma once

// #include "RobotControlData.h"
// #include "RobotControlData.h"
// #include "rev/SparkMax.h"
// #include "rev/SparkAbsoluteEncoder.h"
// #include "rev/SparkClosedLoopController.h"
// #include <frc/Timer.h>
// #include <frc/trajectory/TrapezoidProfile.h>
// #include <units/length.h>
// #include <units/velocity.h>
// #include <units/angle.h>
// #include <units/acceleration.h>
// #include <units/angular_velocity.h>
// #include <units/angular_acceleration.h>
// #include <frc/trajectory/TrapezoidProfile.h>
// #include <frc/smartdashboard/SmartDashboard.h>
// #include <frc/DigitalInput.h>

#include "HAL/AlgaeRemoverHAL.h"

// half of these are probably not needed

class AlgaeRemoverManager
{
public:
    // TODO: set constructor equal to default
    AlgaeRemoverManager();
    ~AlgaeRemoverManager() = default;

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
private:
    AlgaeRemover m_AlgaeRemover;
    // TODO: add bool to represent going to stow position (inside robot)
    bool m_pivotAngleToTop = false;
    bool m_pivotAngleToBottom = false;
    // TODO: get rid of below member variable
    double m_pivotAngle;
    // TODO: this should come from mechanism config... get rid from here
    double m_pivotAngleToRemoveTop = 45.0; //this will probably change later depending on arm design. this is just for default
    double m_pivotAngleToRemoveBottom = 45.0; //this will probably change later depending on arm design. this is just for default
    // TODO: get rid of all member variables below
    double m_RemoverSpeed = 0.0;
    units::second_t m_RemoverTime = 2.0_s;
    frc::Timer m_removerTimer;
};
