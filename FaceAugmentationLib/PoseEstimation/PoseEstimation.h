/*
* Description: Head Pose estimation using OpenCV.
*
* @author João Otávio Brandão (jobal@cin.ufpe.br)
* @since 2018-04-30
*/

#pragma once

#ifdef POSEESTIMATION_EXPORTS  
#define POSEESTIMATION_API __declspec(dllexport)   
#else  
#define POSEESTIMATION_API __declspec(dllimport)   
#endif 

#include <opencv2\opencv.hpp>
#include <windows.h>

class PoseEstimation 
{
public:
	/**
	* Represents the camera parameters.
	*/
	struct CameraInternals
	{
	public:
		cv::Mat A;
		cv::Mat R;
		cv::Mat T;
		cv::Mat distCoeffs;
	};

	static POSEESTIMATION_API PoseEstimation& Instance();

	/**
	* Constructor
	*/
	POSEESTIMATION_API PoseEstimation();

	/**
	* Finds an object pose from 3D-2D point correspondence.
	*
	* @param modelPoints The 3D object points.
	* @param imagePoints The 2D image points.
	* @param cameraInternals The camera parameters.
	* @param ransac Flag for performing RANSAC.
	* @param rotationVector The ouput rotation vector.
	* @param translationVector The output translation vector.
	*/
	POSEESTIMATION_API void EstimateHeadPose(std::vector<cv::Point3d> modelPoints, std::vector<cv::Point2d> imagePoints,
											CameraInternals cameraInternals, bool ransac, cv::Mat &rotationVector, cv::Mat &translationVector);

	/**
	* Computes projections of 3D points to the image plane given intrisic
	* and extrinsic camera parameters.
	*
	* @param image The input 2D image.
	* @param modelPoints The 3D corresponence points.
	* @param imagePoints The 2D image points.
	* @param rotationVector The output rotation vector.
	* @param translationVector The output translation vector.
	*/
	POSEESTIMATION_API void ProjectPoints(std::vector<cv::Point3d> modelPoints, CameraInternals cameraInternals,
											cv::Mat rotationVector, cv::Mat translationVector, std::vector<cv::Point2d> &projPoints);
private:
	static PoseEstimation* instance;
};