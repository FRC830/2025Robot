#include "PhotonVisionCamera.h"

PhotonVisionCamera::PhotonVisionCamera(std::string name, frc::Transform3d robotToCamera)
    : m_robotToCam(robotToCamera)
{
    m_camera = std::make_shared<photon::PhotonCamera>(name);
    m_poseEstimator = std::make_shared<photon::PhotonPoseEstimator>(m_aprilTagFieldLayout,
                                                                    photon::PoseStrategy::MULTI_TAG_PNP_ON_COPROCESSOR,
                                                                    robotToCamera);

    m_poseEstimator->SetMultiTagFallbackStrategy(photon::PoseStrategy::LOWEST_AMBIGUITY);

    frc::SmartDashboard::PutData("vision_pose", &m_field);
}


#include <iostream>
std::optional<photon::EstimatedRobotPose> PhotonVisionCamera::GetPose()
{
    std::cout << "got inside getpose" << std::endl;
    std::optional<photon::EstimatedRobotPose> estimate;

    if (!m_LastResultIsEmpty && (GetAprilTagID() != -1))
    {
        estimate = m_poseEstimator->Update(m_lastResult);
        if (estimate.has_value())
        {
            m_field.SetRobotPose(estimate.value().estimatedPose.ToPose2d());
        }
        std::cout << "updated result" << std::endl;
    }

    return estimate;

}

void PhotonVisionCamera::SaveResult()
{
    auto results = m_camera->GetAllUnreadResults();
    if (!results.empty())
    {
        m_lastResult = results.back();
        m_LastResultIsEmpty = false;
    }
    else
    {
        m_LastResultIsEmpty = true;
    }
}

int PhotonVisionCamera::GetAprilTagID()
{
    int id = -1;
    if (!m_LastResultIsEmpty && m_lastResult.HasTargets())
    {
        auto targets = m_lastResult.GetTargets();
        double lowestYaw = 360.0f;
        double targetId = id;
        for (const auto& target : targets)
        {
            if (std::fabs(target.GetYaw()) < lowestYaw)
            {
                lowestYaw = std::fabs(target.GetYaw());
                targetId = target.GetFiducialId();
            }
        }
        id = targetId;
        // photon::PhotonTrackedTarget target = m_lastResult.GetBestTarget();
        // id = target.GetFiducialId();
    }
    return id;
}

