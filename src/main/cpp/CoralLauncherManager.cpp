#include "CoralLauncherManager.h"
void CoralLauncherManager::resetState() {
    m_SiddhantPandit.SetFlywheelSpeed(0);
    m_SiddhantPandit.SetIndexerSpeed(0);
}
void CoralLauncherManager::handleInput(RobotControlData &controlData) {
    m_SiddhantPandit.SetFlywheelSpeed(controlData.coralInput.flywheelSpeed);
    m_SiddhantPandit.SetIndexerSpeed(controlData.coralInput.indexerSpeed);
}