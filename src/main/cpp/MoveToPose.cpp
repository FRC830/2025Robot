// TODO: this should be in a header file under include/... functions are implemented in the cpp file
// TODO: what do all header files start with?

#include <frc/geometry/Pose2d.h>
#include <cmath>

// TODO: look at these files to understand how to setup and use a trapezoid move using switch statements
         - https://github.com/FRC830/2024Robot/blob/master/src/main/include/subsystems/IntakeHAL.h (trapezoid move member variable init)
         - https://github.com/FRC830/2024Robot/blob/master/src/main/cpp/subsystems/IntakeHAL.cpp (ProfiledMoveToAngle function)


// TODO: don't worry about doing anything with the drive base for now
class MoveToPose
{
    private:
    
    public:
        MoveToPose() = default;
        ~MoveToPose() = default;

        // TODO: Create a top level function that takes in a SINGLE frc::Pose2d called 'desired'

        // TODO: create a function that takes a TWO frc::Pose2d called 'initial' and 'desired'
        //       - this function gets called by the first one and we will use swerve odometry to generate the 'initial'
        //       - this function will call two functions to handle the linear translation, and the angular rotation of the drive base

        // TODO: create a function to handle the angular translation of the drivebase (this will implement a trapezoid move)
        //       - should return the desired degrees_per_second_t the drive base should rotate by

        // TODO: create a function to handle the linear translation of the drivebase (this will implement a trapezoid move)
        //       - this uses the math we did using the distance formula and then splitting it up into th vx and vy component
        //       - should return vx and vy as feet_per_second_t

        // TODO: create helper functions as needed
         
}