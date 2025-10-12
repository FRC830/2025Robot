#pragma once

struct CoralInput{
    double INDEXER_SPEED;
    double FLYWHEEL_SPEED;
};

struct CoralOutput{
    double leftSpeed;
    double rightSpeed;    
};

struct RobotControlData {
    CoralInput KavinsCoralInput;
    CoralOutput KavinsCoralOutput;
};
