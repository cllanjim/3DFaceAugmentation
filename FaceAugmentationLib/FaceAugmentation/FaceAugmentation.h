/*
* Description: 3D facial augmentation for Augmented Reality purpose.
*
* @author João Otávio Brandão (jobal@cin.ufpe.br)
* @since 2018-04-06
*/

#pragma once

#ifdef FACEAUGMENTATION_EXPORTS  
#define FACEAUGMENTATION_API __declspec(dllexport)   
#else  
#define FACEAUGMENTATION_API __declspec(dllimport)   
#endif

#include "SeetaFaceDetection.h"
#include "FeatureExtraction.h"
#include "PoseEstimation.h"
#include <opencv2\features2d.hpp>
#include "opencv2\xfeatures2d.hpp"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <windows.h>

class FaceAugmentation
{
public:
	static FACEAUGMENTATION_API FaceAugmentation& Instance();

	/**
	* Constructor
	*/
	FACEAUGMENTATION_API FaceAugmentation();

	FACEAUGMENTATION_API void ExtractFacialFeatures(BYTE* pixels, FeatureExtraction::Features &features, int width, int height, 
		FeatureExtraction::DescriptorType descriptorType, FeatureExtraction::DetectorType detectorType, SeetaFaceDetection::Face face);

	FACEAUGMENTATION_API void ExtractFacialFeatures(BYTE* pixels, FeatureExtraction::Features &features, int width, int height,
		FeatureExtraction::DescriptorType descriptorType, FeatureExtraction::DetectorType detectorType, bool cropFace);

	FACEAUGMENTATION_API void Create2D3DCorrespondences(std::vector<cv::DMatch> matches, std::vector<cv::KeyPoint> imageKeypoints,
		std::vector<cv::Point3d> model3Dpoints, std::vector<cv::Point2d> &imagePoints, std::vector<cv::Point3d> &modelPoints);

private:
	static FaceAugmentation* instance;
};

