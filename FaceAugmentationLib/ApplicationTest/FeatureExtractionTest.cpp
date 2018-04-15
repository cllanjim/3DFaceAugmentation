/**
*
* This is a test for feature extraction task using OpenCV detectors and descriptors.
*
*/

#include "FeatureExtraction.h"

int main()
{
	cv::Mat image = cv::imread("../../../Dataset/Images/Faces/0000004.jpg");

	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::ORB;
	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::ORB;
	
	FeatureExtraction::Feature feature = FeatureExtraction::Instance().ExtractFeatures(image.data, image.cols, image.rows, descriptorType, detectorType);

	cv::drawKeypoints(image, feature.keypoints, image, cv::Scalar(0, 255, 0));

	cv::imshow("keypoints", image);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}