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
    bool disableFlywheels;
};

struct CoralOutput{
    bool isBeamBroken;
    double leftSpeed;
    double rightSpeed;
    bool flywheelsAtSpeed;
};

struct SmartPlannerInput
{
    bool Left_L1;
    bool Right_L1;
    bool Left_L2;
    bool Right_L2;
};

struct AlgaeInput {
    bool RunRemoverTop; 
    bool RunRemoverBottom;
};

struct AlgaeOutput {
    double RemoverSpeed;
    double PivotAngle;
};

struct RobotControlData {
    SwerveInput swerveInput;
    CoralInput coralInput;
    CoralOutput coralOutput;
    SmartPlannerInput plannerInput;
    AlgaeInput algaeInput;
    AlgaeOutput algaeOutput;

};


