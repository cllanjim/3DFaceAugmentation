#pragma once

#ifdef FEATUREEXTRACTION_EXPORTS  
#define FEATUREEXTRACTION_API __declspec(dllexport)   
#else  
#define FEATUREEXTRACTION_API __declspec(dllimport)   
#endif 

#include <opencv2\features2d.hpp>
#include <opencv2\opencv.hpp>
#include <windows.h>

class FeatureExtraction
{
public:
	struct Feature {
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptor;
	};

	enum ExtractorType{
		ORB
	};

	static FEATUREEXTRACTION_API FeatureExtraction& Instance();
	FEATUREEXTRACTION_API FeatureExtraction();
	FEATUREEXTRACTION_API FeatureExtraction::Feature ExtractFeatures(BYTE* pixels, int width, int height, ExtractorType extractorType);

private:
	static FeatureExtraction* instance;
};