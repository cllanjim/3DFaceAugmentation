/**
*
* This is a test for head pose estimation purposes.
*
*/
#include "PoseEstimation.h"
#include "Utilities.h"

int main()
{		
	cv::Mat image = cv::imread("../../../Dataset/Images/Faces/0000004.jpg");
	std::string featuresFilename = "../../../Matlab/features.txt";

	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::ORB;
	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::ORB;

	FeatureExtraction::Feature feature = Utility::Instance().ExtractFacialFeatures
	(image.data, image.cols, image.rows, descriptorType, detectorType, "");

	if (feature.keypoints.size() == 0)
	{
		std::cout << "No image points found." << std::endl;
		return -1;
	}
	std::vector<cv::Point2d> imagePoints = Utility::Instance().ParseKeyPointsTo2DPoints(feature.keypoints);

	std::string points3DFilename = "../../../Matlab/3D_points.txt";
	std::vector<cv::Point3d> modelPoints = Utility::Instance().Read3DPoints(points3DFilename);

	if (modelPoints.size() == 0)
	{
		std::cout << "No model points found." << std::endl;
		return -1;
	}

	cv::Mat rotationVector; // Rotation in axis-angle form
	cv::Mat translationVector;

	PoseEstimation::Instance().EstimateHeadPose(image, modelPoints, imagePoints, rotationVector, translationVector);

	std::cout << "Rotation Vector " << std::endl << rotationVector << std::endl;
	std::cout << "Translation Vector" << std::endl << translationVector << std::endl;

	system("pause");

	return 0;
}