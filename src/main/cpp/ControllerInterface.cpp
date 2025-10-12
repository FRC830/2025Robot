#include "ControllerInterface.h"

void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData){
    if (controller.GetBButton()){
        controlData.DataCORAL_INPUT.IndexerSpeed = 0.3;
    }
    else{
        controlData.DataCORAL_INPUT.IndexerSpeed = 0.0;
    }
     if (controller.GetYButton()){
        controlData.DataCORAL_INPUT.FlyWheelSpeed = 0.3;
    }
    else{
        controlData.DataCORAL_INPUT.FlyWheelSpeed = 0.0;
    }
}

void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData){
    UpdateLauncherInput(controlData);
}
