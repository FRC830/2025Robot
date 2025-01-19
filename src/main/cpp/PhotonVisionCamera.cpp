#include "PhotonVisionCamera.h"

PhotonVisionCamera::PhotonVisionCamera(std::string name, frc::Transform3d robotToCamera)
    : m_robotToCam(robotToCamera)
{
    m_camera = std::make_shared<photon::PhotonCamera>(name);
    m_poseEstimator = std::make_shared<photon::PhotonPoseEstimator>(m_aprilTagFieldLayout,
                                                                    photon::PoseStrategy::MULTI_TAG_PNP_ON_COPROCESSOR,
                                                                    robotToCamera);

    m_poseEstimator->SetMultiTagFallbackStrategy(photon::PoseStrategy::LOWEST_AMBIGUITY);
}
std::optional<photon::EstimatedRobotPose> PhotonVisionCamera::GetPose()
{
    // Get the latest result from the camera
    // auto results = m_camera->GetAllUnreadResults();
    // photon::PhotonPipelineResult pipeline_result;
    // // if (!results.empty()) {
    //     pipeline_result = results.back();
    // //}
    // auto result = m_poseEstimator->Update(pipeline_result);
    // return result;

    auto result = m_camera->GetLatestResult();
    // if(result.MultiTagResult().result.isPresent){
    //     frc::Transform3d fieldToCamera = result.MultiTagResult().result.best;
    // }
    auto estimate = m_poseEstimator->Update(result);

    return estimate;

}