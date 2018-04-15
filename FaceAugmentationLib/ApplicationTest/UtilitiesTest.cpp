/**
*
* This is a test for the utilities functions.
*
*/
#include "Utilities.h"

void ExtractFaceFeaturesTest();

int main()
{
	ExtractFaceFeaturesTest();
}

void ExtractFaceFeaturesTest()
{
	cv::Mat image = cv::imread("../../../Dataset/Images/Faces/0000004.jpg");

	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::STAR;
	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::LUCID;

	Utility::Instance().ExtractFaceFeatures(image.data, image.cols, image.rows, descriptorType, detectorType, "features.txt");
}