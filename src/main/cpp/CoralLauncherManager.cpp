#include "CoralLauncherManager.h"

void CoralLauncherManager::ResetState(RobotControlData &controlData){
    controlData.DataCORAL_INPUT.FlyWheelSpeed = 0.0;
    controlData.DataCORAL_INPUT.IndexerSpeed = 0.0;
};

void CoralLauncherManager::HandleInput(RobotControlData &controlData){
    m_launcher.SetFlyWheelSpeed(controlData.DataCORAL_INPUT.FlyWheelSpeed);
    m_launcher.SetIndexerSpeed(controlData.DataCORAL_INPUT.IndexerSpeed);
};