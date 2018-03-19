#include "FeatureExtraction.h"

int main()
{
	cv::Mat image = cv::imread("../../../Dataset/Images/Faces/0000003.jpg");
	FeatureExtraction::ExtractorType extractorType = FeatureExtraction::ExtractorType::ORB;
	FeatureExtraction::Feature feature = FeatureExtraction::Instance().ExtractFeatures(image.data, image.cols, image.rows, extractorType);
	cv::imshow("descriptor", feature.descriptor);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}