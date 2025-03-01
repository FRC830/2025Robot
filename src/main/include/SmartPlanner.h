#pragma once

#include "MoveToPose.h"
#include "PhotonVisionCamera.h"
#include "ratpack/swerve/WPISwerveDrive.h"
#include "RobotControlData.h"
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include "ScoringPositionMap.h"
#include <units/length.h>


class SmartPlanner{
    public:
        SmartPlanner(PhotonVisionCamera &cam, WPISwerveDrive &swerve);
        ~SmartPlanner() = default;

        void HandleInput(RobotControlData &data);

    private:
        SmartPlanner() = default;
        void SmartPlan(RobotControlData &data);

        PhotonVisionCamera &m_Cam;
        MoveToPose m_moveToPose;
        WPISwerveDrive &m_Swerve;
        int m_state;
        frc::Pose2d m_targetPose;
        frc::Pose2d m_startPose;
        int m_tagId;

        ScoringPositionMap m_positionMap;
};