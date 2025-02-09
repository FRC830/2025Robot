#pragma once

#include <rev/config/SparkMaxConfig.h>

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
}