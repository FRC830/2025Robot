#pragma once

struct SwerveInput{
    double xTranslation;
    double yTranslation;
    double rotation;

    bool targetLeftFeederAngle;
    bool targetRightFeederAngle;
    bool goFieldOriented;
};

struct ResetNavx
{
    bool reset;
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

struct ClimberInput{
    // bool Unspool;
    // bool Respool;
    double ClimberSpeed;
};

struct ClimberOutput{
    double ClimberSpeed;
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
    bool RunRemoverStow;
};

struct AlgaeOutput {
    double RemoverSpeed;
    double PivotAngle;
};

struct RobotControlData {
    SwerveInput swerveInput;
    CoralInput coralInput;
    CoralOutput coralOutput;
    ClimberInput climberInput;
    ClimberOutput climberOutput;
    SmartPlannerInput plannerInput;
    AlgaeInput algaeInput;
    AlgaeOutput algaeOutput;
    ResetNavx resetNavx;

};


