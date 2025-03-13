#pragma once

#include <rev/config/SparkMaxConfig.h>
#include "PhotonVisionCamera.h"
#include <ctre/phoenix6/TalonFX.hpp>
#include <ctre/phoenix6/configs/Configs.hpp>

namespace {
namespace ratbot
{

    const double VOLTAGE_COMPENSATION = 10.5f;

    namespace CoralLauncherConfig
    {
        namespace Flywheel
        {
            const double P = 0.00025;
            const double I = 0.0;
            const double D = 0.35;
            const double F = 0.0;
            const double VEL_CONV_FACTOR = 1.0;
            const double CURRENT_LIM = 30.0;
            const bool INVERTED = true;
            rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kCoast;
        }

        namespace Indexer
        {
            const double CURRENT_LIM = 20.0;
            const bool INVERTED = true;
            rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kCoast;
        } 
    }

    namespace ClimberConfig
    {
        const double MAX_ANGLE = 90.0;
        const double MIN_ANGLE = 0.0;
        const double P = 0.00025;
        const double I = 0.0;
        const double D = 0.35;
        const double F = 0.0;
        const double VEL_CONV_FACTOR = 1.0;
        const double CURRENT_LIM = 30.0;
        const bool INVERTED = false;
        rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kBrake;
    }

    namespace IntakeConfig
    {
        frc::Rotation2d ROTATION_TO_FEEDER = frc::Rotation2d(units::degree_t{234.0});
    }
    namespace VisionConfig
    {
        frc::Transform3d ROBOT_TO_CAMERA = frc::Transform3d(frc::Translation3d(11_in, 1.625_in, 23.5_in), frc::Rotation3d(0_rad, -23_deg, 0_rad));
    }
  
    namespace AlgaeRemoverConfig
    {
        namespace Pivot
        {
            const double MAX_PIVOT_ANGLE = 106.0;
            const double MIN_PIVOT_ANGLE = 0.0;
            const double TOP_REMOVER_POS = 100.0; // TODO: Tune
            const double BOTTOM_REMOVER_POS = 45.0; // TODO: Tune
            const double STOW_REMOVER_POS = 0.0;
            const double P = 2.4; // TODO: Tune (An error of 1 rotation results in 2.4 V output)
            const double I = 0.0; // TODO: Tune (no output for integrated error)
            const double D = 0.1; // TODO: Tune (A velocity of 1 rps results in 0.1 V output)
            units::dimensionless::scalar_t POS_CONV_FACTOR = 1.0; // TODO: Tune
            units::current::ampere_t CURRENT_LIM = 30_A;
            ctre::phoenix6::signals::InvertedValue INVERTED = false; 
            ctre::phoenix6::signals::NeutralModeValue IDLE_MODE = ctre::phoenix6::signals::NeutralModeValue::Brake;
        }

        namespace Remover
        {
            const double CURRENT_LIM = 20.0;
            const bool INVERTED = false;
            const double REMOVER_SPEED = 0.1f;
            rev::spark::SparkBaseConfig::IdleMode IDLE_MODE = rev::spark::SparkBaseConfig::IdleMode::kCoast;
        }
    }

    namespace MoveToPoseConfig
    {
        // TODO: tune values on carpet
        const double MAX_TURN_SPEED_DEG_PER_SEC = 120.0f;
        const double TURN_FEED_FORWARD_DEG_PER_SEC = 10.0f;
        const double MAX_SPEED_M_PER_SEC = 0.0f; // todo: change!!!
        const double SPEED_FEED_FORWARD_M_PER_SEC = 0.0f; //todo: change!!!!!
    }
}
}