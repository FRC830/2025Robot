#include "CoralLauncherHAL.h"
#include <rev/config/SparkMaxConfig.h>

CoralLauncher::CoralLauncher()
{
    rev::spark::SparkMaxConfig flywheel_config{};
    rev::spark::SparkMaxConfig indexer_config{};


};

void CoralLauncher::SetIndexerSpeed(double speed){
    IndexerRight.Set(speed);
    IndexerLeft.Set(speed);
};

void CoralLauncher::SetFlyWheelSpeed(double speed){
    FlyWheelRight.Set(speed);
    FlyWheelLeft.Set(speed);
};

