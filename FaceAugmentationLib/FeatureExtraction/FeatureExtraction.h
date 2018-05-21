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
	* Represents the features extracted from a feature detector and descriptor.
	*/
	struct Features {
		std::vector<cv::KeyPoint> keypoints;
		int keypointsSize = 0;
		cv::Mat descriptors;	
		int descriptorsWidth = 0;
		int descriptorsHeight = 0;
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
	* Represents the descriptor matcher.
	*/
	enum class DescriptorMatcher
	{
		BRUTE_FORCE, FLANN_BASED
	};

	static FEATUREEXTRACTION_API FeatureExtraction& Instance();

	/**
	* Constructor
	*/
	FEATUREEXTRACTION_API FeatureExtraction();

	/**
	* Detects keypoints and computes the descriptors.
	*
	* @param image The source image.
	* @param features The struct that stores the keypoints and descriptors.
	* @param descriptorType A constant to indicate which feature descriptor will be applyied.
	* @param detectorType A constant to indicate which feature detector will be applyied.
	*/
	FEATUREEXTRACTION_API void ExtractFeatures(cv::Mat &image, Features &features, DescriptorType descriptorType, DetectorType detectorType);

	/**
	* Detects keypoints and computes the descriptors.
	*
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param features The struct that stores the keypoints and descriptors.
	* @param descriptorType A constant to indicate which feature descriptor will be applyied.
	* @param detectorType A constant to indicate which feature detector will be applyied.
	*/
	FEATUREEXTRACTION_API void ExtractFeatures(BYTE* pixels, int width, int height, Features &features, DescriptorType descriptorType, DetectorType detectorType);

	/**
	* Finds the best match for each descriptor from a query set.
	*
	* @param descriptors1 The first descriptors.
	* @param descriptors2 The second descriptors.
	* @param matches The matches indexes.
	* @param descriptorMatcher A constant to indicate which matcher will be applyied.
	*/
	FEATUREEXTRACTION_API void Match(cv::Mat descriptors1, cv::Mat descriptors2, std::vector<cv::DMatch> &matches, DescriptorMatcher descriptorMatcher);

private:
	static FeatureExtraction* instance;

	/**
	* Initializes the feature descriptor by the descriptor type.
	*
	* @param descriptor The feature descriptor.
	* @param descriptorType A constant to indicate which feature descriptor will be applyied.
	*/
	void SetFeatureDescriptor(cv::Ptr<cv::DescriptorExtractor> &descriptor, DescriptorType descriptorType);

	/**
	* Initializes the feature detector by the detector type.
	*
	* @param descriptor The feature detector.
	* @param descriptorType A constant to indicate which feature detector will be applyied.
	*/
	void SetFeatureDetector(cv::Ptr<cv::FeatureDetector> &detector, DetectorType detectorType);
};