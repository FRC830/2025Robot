#pragma once

#include <string>
#include <photon/PhotonCamera.h>
#include <photon/PhotonPoseEstimator.h>
#include <frc/geometry/Transform3d.h>
#include <frc/apriltag/AprilTagFieldLayout.h>
#include <frc/geometry/Pose3d.h>
#include <memory>
#include <frc/smartdashboard/Field2d.h>
#include <frc/smartdashboard/SmartDashboard.h>

class PhotonVisionCamera
{
    private:
       std::shared_ptr<photon::PhotonCamera> m_camera;
       frc::AprilTagFieldLayout m_aprilTagFieldLayout = frc::AprilTagFieldLayout::LoadField(frc::AprilTagField::kDefaultField);
       frc::Transform3d m_robotToCam;
       std::shared_ptr<photon::PhotonPoseEstimator> m_poseEstimator;
       photon::PhotonPipelineResult m_lastResult;
       frc::Field2d m_field;
       bool m_LastResultIsEmpty;
       PhotonVisionCamera() = default;

    public:    
        PhotonVisionCamera(std::string name, frc::Transform3d robotToCamera);
        std::optional<photon::EstimatedRobotPose> GetPose();
        void SaveResult();
        int GetAprilTagID();
        
};