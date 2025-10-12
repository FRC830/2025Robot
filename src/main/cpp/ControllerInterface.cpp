#include "ControllerInterface.h"

void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData) {
    //lucas yuan
    //kavin murali
    if(LucasYuan.GetAButton())
    {
        controlData.coralInput.indexerSpeed = 0.5;
    }
    else
    {
        controlData.coralInput.indexerSpeed = 0;
    };
    if(LucasYuan.GetBButton())
    {
        controlData.coralInput.flywheelSpeed = 0.1;
    }
    else
    {
        controlData.coralInput.flywheelSpeed = 0;
    };
}
void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData) {

UpdateLauncherInput(controlData);
}
