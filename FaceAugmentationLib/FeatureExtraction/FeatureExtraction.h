#pragma once

#ifdef FEATUREEXTRACTION_EXPORTS  
#define FEATUREEXTRACTION_API __declspec(dllexport)   
#else  
#define FEATUREEXTRACTION_API __declspec(dllimport)   
#endif 

#include <opencv2\features2d.hpp>
#include "opencv2/xfeatures2d.hpp"
#include <opencv2\opencv.hpp>
#include <windows.h>

class FeatureExtraction
{
public:
	struct Feature {
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		int keypointsSize;
		int descWidth;
		int descHeight;
	};

	enum class DetectorType 
	{
		AGAST, AKAZE, BRISK, FAST, GFFT, KAZE, MSDD, MSER, ORB, SBD, SIFT, STAR, SURF
	};

	enum class DescriptorType
	{
		AKAZE, BRIEF, BRISK, DAISY, FREAK, KAZE, LATCH, LUCID, ORB, SIFT, SURF
	};

	static FEATUREEXTRACTION_API FeatureExtraction& Instance();
	FEATUREEXTRACTION_API FeatureExtraction();
	FEATUREEXTRACTION_API FeatureExtraction::Feature ExtractFeatures(BYTE* pixels, int width, int height, DescriptorType descriptorType, DetectorType detectorType);

private:
	static FeatureExtraction* instance;
	std::vector<cv::KeyPoint> DetectFeatures(BYTE* pixels, int width, int height, DetectorType detectorType);
};