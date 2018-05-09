/**
*
* This is a test for head pose estimation purposes.
*
*/
#include "PoseEstimation.h"
#include "Utilities.h"

void onMouse(int evt, int x, int y, int flags, void* param);

int main()
{		
	cv::Mat image = cv::imread("../../../Dataset/Images/Faces/headPose.jpg");
	std::string featuresFilename = "../../../Matlab/features1.txt";

	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::ORB;
	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::ORB;

	FeatureExtraction::Feature feature = Utility::Instance().ExtractFacialFeatures
	(image.data, image.cols, image.rows, descriptorType, detectorType, "");

	if (feature.keypoints.size() == 0)
	{
		std::cout << "No image points found." << std::endl;
		return -1;
	}

	cv::Mat imageCopy;
	image.copyTo(imageCopy);
	cv::drawKeypoints(imageCopy, feature.keypoints, imageCopy, cv::Scalar(0, 255, 0));

	std::vector<cv::Point2d> clickedPoints;
	cv::namedWindow("keypoints");
	cv::setMouseCallback("keypoints", onMouse, (void*)&clickedPoints);
	cv::imshow("keypoints", imageCopy);

	std::vector<cv::Point2d> imagePoints = Utility::Instance().ParseKeyPointsTo2DPoints(feature.keypoints);

	std::string points3DFilename = "../../../Matlab/3D_points2.txt";
	std::vector<cv::Point3d> modelPoints = Utility::Instance().Read3DPoints(points3DFilename);

	if (modelPoints.size() == 0)
	{
		std::cout << "No model points found." << std::endl;
		return -1;
	}

	cv::Mat rotationVector; // Rotation in axis-angle form
	cv::Mat translationVector;

	PoseEstimation::CameraInternals cameraInternals = { image };

	PoseEstimation::Instance().EstimateHeadPose(image, modelPoints, imagePoints, cameraInternals, false, rotationVector, translationVector);

	std::cout << "Camera Matrix " << std::endl << cameraInternals.cameraMatrix << std::endl;
	std::cout << "Rotation Vector " << std::endl << rotationVector << std::endl;
	std::cout << "Translation Vector" << std::endl << translationVector << std::endl;

	std::vector<int> indexes = { 0, 10, 20, 30 };
	std::vector<cv::Point3d> endModelPoints;
	for (int i = 0; i < indexes.size(); i++)
		endModelPoints.push_back(modelPoints.at(i));

	std::vector<cv::Point2d> projPoints;
	PoseEstimation::Instance().ProjectPoints(endModelPoints, cameraInternals, rotationVector, translationVector, projPoints);

	std::cout << "Projected points" << std::endl << projPoints << std::endl;

	cv::Mat outputImage;
	image.copyTo(outputImage);

	std::vector<cv::Point2d> endImagePoints;
	for (int i = 0; i < indexes.size(); i++)
		endImagePoints.push_back(imagePoints.at(i));

	Utility::Instance().DrawLines(endImagePoints, projPoints, outputImage);

	cv::imshow("Output", outputImage);

	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}

void onMouse(int evt, int x, int y, int flags, void* param) {
	if (evt == CV_EVENT_LBUTTONDOWN) {
		std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
		ptPtr->push_back(cv::Point(x, y));
		std::cout << "(" << x << ", " << y << ")" << std::endl;
	}
}