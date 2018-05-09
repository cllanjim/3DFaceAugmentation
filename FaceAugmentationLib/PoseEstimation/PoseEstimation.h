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
		/**
		* Approximate focal length.
		*/
		double focalLength;
		/**
		* Image center.
		*/
		cv::Point2d center;
		/**
		* 
		*/
		cv::Mat cameraMatrix;
		/**
		* Assuming no lens distortion
		*/
		cv::Mat distCoeffs;

		CameraInternals() {}

		CameraInternals(cv::Mat image) 
		{
			focalLength = image.cols;
			center = cv::Point2d(image.cols / 2, image.rows / 2);
			cameraMatrix = (cv::Mat_<double>(3, 3) << focalLength, 0, center.x, 0, focalLength, center.y, 0, 0, 1);
			distCoeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type);
		}

		CameraInternals(double fl, cv::Point2d ct) 
		{
			focalLength = fl;
			center = ct;
			cameraMatrix = (cv::Mat_<double>(3, 3) << focalLength, 0, center.x, 0, focalLength, center.y, 0, 0, 1);
			distCoeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type);
		}
	};

	/**
	* Public static singleton instance.
	*/
	static POSEESTIMATION_API PoseEstimation& Instance();

	/**
	* Constructor
	*/
	POSEESTIMATION_API PoseEstimation();

	/**
	* Calculate the head pose of faces in 2D images.
	*
	* @param image The input 2D image.
	* @param modelPoints The 3D corresponence points.
	* @param imagePoints The 2D image points.
	* @param rotationVector The output rotation vector.
	* @param translationVector The output translation vector.
	*/
	POSEESTIMATION_API void EstimateHeadPose(cv::Mat image, std::vector<cv::Point3d> modelPoints, std::vector<cv::Point2d> imagePoints,
												CameraInternals cameraInternals, bool ransac, cv::Mat &rotationVector, cv::Mat &translationVector);


	POSEESTIMATION_API void ProjectPoints(std::vector<cv::Point3d> modelPoints, CameraInternals cameraInternals,
											cv::Mat rotationVector, cv::Mat translationVector, std::vector<cv::Point2d> &projPoints);
private:
	/**
	* Private static singleton instance.
	*/
	static PoseEstimation* instance;
};