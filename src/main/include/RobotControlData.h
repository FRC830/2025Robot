#pragma once

#include "inputManager/CoralLauncherManager.h"

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;

    bool targetLeftFeederAngle;
    bool targetRightFeederAngle;
};

struct RobotControlData {
    SwerveInput swerveInput;
    CoralInput launcherInput;

};

