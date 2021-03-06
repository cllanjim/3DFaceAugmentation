#include "PoseEstimation.h"

PoseEstimation* PoseEstimation::instance = NULL;

PoseEstimation::PoseEstimation() { }

PoseEstimation& PoseEstimation::Instance()
{
	if (!instance)
	{
		instance = new PoseEstimation();
	}

	return *instance;
}

void PoseEstimation::EstimateHeadPose(std::vector<cv::Point3d> modelPoints, std::vector<cv::Point2d> imagePoints,
										CameraInternals cameraInternals, bool ransac, cv::Mat &rotationVector, cv::Mat &translationVector)
{
	rotationVector = cameraInternals.R;
	translationVector = cameraInternals.T;

	if (!ransac)
		cv::solvePnP(modelPoints, imagePoints, cameraInternals.A, cameraInternals.distCoeffs, rotationVector, translationVector);
	else
		cv::solvePnPRansac(modelPoints, imagePoints, cameraInternals.A, cameraInternals.distCoeffs, rotationVector, translationVector);
}


void PoseEstimation::ProjectPoints(std::vector<cv::Point3d> modelPoints, CameraInternals cameraInternals,
									cv::Mat rotationVector, cv::Mat translationVector, std::vector<cv::Point2d> &projPoints)
{
	cv::projectPoints(modelPoints, rotationVector, translationVector, cameraInternals.A, cameraInternals.distCoeffs, projPoints);
}