#include "CoralLauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>


CoralLauncher::CoralLauncher()
{
    rev::spark::SparkMaxConfig flywheel_config{};
    rev::spark::SparkMaxConfig indexer_config{};
};

void CoralLauncher::SetIndexerSpeed(double speed) {
    Indexer_Left.Set(speed);
    Indexer_Right.Set(speed);
};

void CoralLauncher::SetFlywheelSpeed(double speed) {
    Flywheel_Left.Set(speed);
    Flywheel_Right.Set(speed);
};
