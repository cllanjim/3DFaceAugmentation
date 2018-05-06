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
											cv::Mat &rotationVector, cv::Mat &translationVector);
private:
	/**
	* Private static singleton instance.
	*/
	static PoseEstimation* instance;
};