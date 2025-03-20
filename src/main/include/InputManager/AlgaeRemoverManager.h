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
    AlgaeRemoverManager() = default;
    ~AlgaeRemoverManager() = default;

    void ResetState(RobotControlData &robotControlData);
    void HandleInput(RobotControlData &robotControlData);

private:
    AlgaeRemover m_AlgaeRemover;
    bool m_pivotAngleToTop = false;
    bool m_pivotAngleToStow = false;
    bool m_pivotAngleToBottom = false;

};
