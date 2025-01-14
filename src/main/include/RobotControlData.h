#pragma once

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;
};

struct RobotControlData {
    SwerveInput swerveInput;
};

