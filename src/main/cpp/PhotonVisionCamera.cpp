#include "PhotonVisionCamera.h"

PhotonVisionCamera::PhotonVisionCamera(std::string name, frc::Transform3d robotToCamera)
    : robotToCam(robotToCamera)
{
    camera = std::make_shared<photon::PhotonCamera>(name);
    poseEstimator = std::make_shared<photon::PhotonPoseEstimator>(aprilTagFieldLayout,
                                                                  photon::PoseStrategy::MULTI_TAG_PNP_ON_COPROCESSOR,
                                                                  robotToCamera);

    poseEstimator->SetMultiTagFallbackStrategy(photon::PoseStrategy::LOWEST_AMBIGUITY);
}
std::optional<photon::EstimatedRobotPose> PhotonVisionCamera::GetPose()
{
    // Get the latest result from the camera
    auto results = camera->GetAllUnreadResults();
    photon::PhotonPipelineResult pipeline_result;
    if (!results.empty()) {
        pipeline_result = results.back();
    }
    auto result = poseEstimator->Update(pipeline_result);
    return result;

}