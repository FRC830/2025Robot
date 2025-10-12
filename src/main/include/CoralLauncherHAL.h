#pragma once

#include "CanConfig.h"
#include "RobotControlData.h"
#include "rev/SparkMax.h"
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

class CoralLauncher
{
    public:
        CoralLauncher();
        ~CoralLauncher() = default; 
        void SetIndexerSpeed(double speed);
        void SetFlyWheelSpeed(double speed);

    private:
        rev::spark::SparkMax FlyWheelRight{CORAL_LAUNCHER_FLYWHEEL_RIGHT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax FlyWheelLeft{CORAL_LAUNCHER_FLYWHEEL_LEFT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax IndexerRight{CORAL_LAUNCHER_INDEXER_RIGHT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax IndexerLeft{CORAL_LAUNCHER_INDEXER_LEFT_CAN_ID, rev::spark::SparkMax::MotorType::kBrushless};

};
