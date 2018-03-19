#include "FeatureExtraction.h"

FeatureExtraction* FeatureExtraction::instance = NULL;

FeatureExtraction::FeatureExtraction() { }

FeatureExtraction& FeatureExtraction::Instance()
{
	if (!instance)
	{
		instance = new FeatureExtraction();
	}

	return *instance;
}

FeatureExtraction::Feature FeatureExtraction::ExtractFeatures(BYTE* pixels, int width, int height, ExtractorType extractorType)
{
	cv::Mat img(height, width, CV_8UC3, pixels);
	cv::Ptr<cv::ORB> orb = cv::ORB::create();

	std::vector<cv::KeyPoint> keypoints;
	cv::Mat descriptor;

	orb->detect(img, keypoints);
	orb->compute(img, keypoints, descriptor);

	// Use both methods above or just it
	//orb->detectAndCompute(img, cv::noArray(), keypoints, descriptor);

	Feature feature = {
		keypoints,
		descriptor
	};

	return feature;
}
