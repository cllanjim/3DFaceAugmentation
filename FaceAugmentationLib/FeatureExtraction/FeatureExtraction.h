/*
* Description: Feature extraction using OpenCV and OpenCV contrib.
*
* @author João Otávio Brandão (jobal@cin.ufpe.br)
* @since 2018-03-30
*/

#pragma once

#ifdef FEATUREEXTRACTION_EXPORTS  
#define FEATUREEXTRACTION_API __declspec(dllexport)   
#else  
#define FEATUREEXTRACTION_API __declspec(dllimport)   
#endif 

#include <opencv2\features2d.hpp>
#include "opencv2\xfeatures2d.hpp"
#include <opencv2\opencv.hpp>
#include <windows.h>

class FeatureExtraction
{
public:
	/**
	* Represents the extracted feature.
	*/
	struct Feature {
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		int keypointsSize = 0;
		int descWidth;
		int descHeight;
	};

	/**
	* Represents the feature detector.
	*/
	enum class DetectorType 
	{
		AGAST, AKAZE, BRISK, FAST, GFFT, KAZE, MSDD, MSER, ORB, SBD, SIFT, STAR, SURF
	};

	/**
	* Represents the feature descriptor.
	*/
	enum class DescriptorType
	{
		AKAZE, BRIEF, BRISK, DAISY, FREAK, KAZE, LATCH, LUCID, ORB, SIFT, SURF
	};

	/**
	* Public static singleton instance.
	*/
	static FEATUREEXTRACTION_API FeatureExtraction& Instance();

	/**
	* Constructor
	*/
	FEATUREEXTRACTION_API FeatureExtraction();

	/**
	* Extract features from a image.
	*
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param descriptorType The OpenCV descriptor type.
	* @param detectorType The OpenCV detector type.
	* @return Struct containing extracted feature information.
	*/
	FEATUREEXTRACTION_API FeatureExtraction::Feature ExtractFeatures(BYTE* pixels, int width, int height, DescriptorType descriptorType, DetectorType detectorType);

private:
	/**
	* Private static singleton instance.
	*/
	static FeatureExtraction* instance;

	/**
	* Detect features from a image.
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param detectorType The OpenCV detector type.
	* @return Vectir containing the image keypoints.
	*/
	std::vector<cv::KeyPoint> DetectFeatures(BYTE* pixels, int width, int height, DetectorType detectorType);
};