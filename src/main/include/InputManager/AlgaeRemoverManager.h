#pragma once

#include "HAL/AlgaeRemoverHAL.h"

// half of these are probably not needed

class AlgaeRemoverManager
{
public:
    AlgaeRemoverManager();
    ~AlgaeRemoverManager() = default;

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
private:
    AlgaeRemover m_AlgaeRemover;
    bool m_pivotAngleToTop = false;
    bool m_pivotAngleToBottom = false;
    double m_pivotAngle;
    double m_pivotAngleToRemoveTop = 45.0; // TODO: Tune this?
    double m_pivotAngleToRemoveBottom = 45.0; // TODO: Tune this?
    double m_RemoverSpeed = 0.0;
    units::second_t m_RemoverTime = 2.0_s;
    frc::Timer m_removerTimer;
};
