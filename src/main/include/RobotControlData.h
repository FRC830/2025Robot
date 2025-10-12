#pragma once

struct CoralInput{
    double indexerSpeed;
    double flywheelSpeed;
};

struct CoralOutput{
    double leftSpeed;
    double rightSpeed;
};

struct RobotControlData {
    CoralInput coralInput;
};