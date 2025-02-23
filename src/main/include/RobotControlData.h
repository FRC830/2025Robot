#pragma once

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;

    bool targetLeftFeederAngle;
    bool targetRightFeederAngle;
};

struct CoralInput{
    double indexerSpeeds;
    bool setFlywheelToL1Speed;
    bool setFlywheelToL2Speed;
};

struct CoralOutput{
    bool isBeamBroken;
    double leftSpeed;
    double rightSpeed;
};

struct RobotControlData {
    SwerveInput swerveInput;
    CoralInput coralInput;
    CoralOutput coralOutput;

};



