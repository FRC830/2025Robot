#include "ControllerInterface.h"

void ControllerInterface::UpdateLauncherInput(RobotControlData &controlData){
    
    if(DavesController.GetAButton()){
        controlData.KavinsCoralInput.FLYWHEEL_SPEED=0.25;
    } else {
        controlData.KavinsCoralInput.FLYWHEEL_SPEED=0.0;
    }
    
    if(DavesController.GetBButton()){
        controlData.KavinsCoralInput.INDEXER_SPEED=0.25;
    } else {
        controlData.KavinsCoralInput.INDEXER_SPEED=0.0;
    }
}


void ControllerInterface::UpdateRobotControlData(RobotControlData &controlData){
   UpdateLauncherInput(controlData);
}

