#include "CoralLauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>


CoralLauncher::CoralLauncher()
{
    rev::spark::SparkMaxConfig flywheel_config{};
    rev::spark::SparkMaxConfig indexer_config{};

}


void CoralLauncher::SetIndexerSpeed(double speed) {
    leftIndexer.Set(speed);
    rightIndexer.Set(speed);
}
void CoralLauncher::SetFlywheelSpeed(double speed) {
    leftFlywheel.Set(speed);
    rightFlywheel.Set(speed);
}