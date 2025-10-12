#include "CoralLauncherManager.h"

void CoralLauncherManager::ResetState() {
    m_launcher.SetFlywheelSpeed(0.0);
    m_launcher.SetIndexerSpeed(0.0);
};





void CoralLauncherManager::HandleInput(RobotControlData &controlData) {
    m_launcher.SetFlywheelSpeed(controlData.KavinsCoralInput.FLYWHEEL_SPEED);
    m_launcher.SetIndexerSpeed(controlData.KavinsCoralInput.INDEXER_SPEED);
};