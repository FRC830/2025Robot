#pragma once

struct CoralInput{
    double IndexerSpeed;
    double FlyWheelSpeed;
};

struct CoralOutput{
    double LeftSpeed;
    double RightSpeed;
};

struct RobotControlData {
    CoralInput DataCORAL_INPUT;
    CoralOutput DataCORAL_OUTPUT;
};
