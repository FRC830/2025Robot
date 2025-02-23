#pragma once

#include <rev/config/SparkMaxConfig.h>
#include "PhotonVisionCamera.h"

namespace {
namespace ratbot
{

    const double VOLTAGE_COMPENSATION = 10.5f;

    namespace CoralLauncherConfig
    {
        namespace Flywheel
        {
            const double P = 0.0;
            const double I = 0.0;
            const double D = 0.0;
            const double F = 0.0;
            const double VEL_CONV_FACTOR = 0.0;
            const double CURRENT_LIM = 0.0;
            const bool INVERTED = false;
            rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kCoast;
        }

        namespace Indexer
        {
            const double CURRENT_LIM = 0.0;
            const bool INVERTED = false;
            rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kCoast;
        } 
    }
    namespace IntakeConfig
    {
        frc::Rotation2d ROTATION_TO_FEEDER = frc::Rotation2d(units::degree_t{90.0});
    }
    namespace VisionConfig
    {
        frc::Transform3d ROBOT_TO_CAMERA = frc::Transform3d(frc::Translation3d(5_m, 0_m, 0.5_m), frc::Rotation3d(0_rad, 0_rad, 0_rad));
    }
}
}