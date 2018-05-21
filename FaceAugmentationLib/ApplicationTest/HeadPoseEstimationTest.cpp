#include "FaceAugmentation.h"
#include "SeetaFaceDetection.h"
#include "Utilities.h"

void SaveKeypoints();
void HeadPoseEstimationTest();

int main()
{
	//SaveKeypoints();
	HeadPoseEstimationTest();
	return 0;
}

void SaveKeypoints()
{
	cv::Mat modelImage = cv::imread("../../../Dataset/Faces/Models/000001/Model_002/000001.jpg");
	std::string file = "../../../Dataset/Faces/Models/000001/Model_002/keypoints.txt";

	if (modelImage.empty())
	{
		std::cout << "The model image is empty!" << std::endl;
		system("pause");
		return;
	}

	FeatureExtraction::Features modelImageFeatures;

	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::ORB;
	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::ORB;

	FaceAugmentation::Instance().ExtractFacialFeatures(modelImage.data, modelImageFeatures, modelImage.cols,
		modelImage.rows, descriptorType, detectorType, false);

	if (modelImageFeatures.keypointsSize == 0)
	{
		std::cout << "No keypoints found in model image!" << std::endl;
		system("pause");
		return;
	}

	Utility::Instance().SaveKeypoints(modelImageFeatures.keypoints, file);
}

void HeadPoseEstimationTest()
{
	cv::Mat inputImage = cv::imread("../../../Dataset/Faces/Images/000001.jpg");
	cv::Mat modelImage = cv::imread("../../../Dataset/Faces/Models/000001/Model_002/000001.jpg");
	std::string inputKeypointsFile = "../../../Dataset/Faces/Models/000001/Model_002/image_keypoints.txt";
	std::string modelKeypointsFile = "../../../Dataset/Faces/Models/000001/Model_002/model_keypoints.txt";
	std::string modelPointsFile = "../../../Dataset/Faces/Models/000001/Model_002/3D_points.txt";
	std::string cameraParamsFile = "../../../Dataset/Faces/Models/000001/Model_002/camera_params.txt";
	/*std::string model2DPointFile = "../../../Dataset/Faces/Models/000001/Model_002/keypoints.txt";
	std::string model3DPointFile = "../../../Dataset/Faces/Models/000001/Model_002/3D_pts.txt";
	std::string cameraParams = "../../../Dataset/Faces/Models/000001/Model_002/camera_params.txt";*/

	if (inputImage.empty())
	{
		std::cout << "The input image is empty!" << std::endl;
		system("pause");
		return;
	}

	if (modelImage.empty())
	{
		std::cout << "The model image is empty!" << std::endl;
		system("pause");
		return;
	}

	int faceCount;
	long long duration;
	SeetaFaceDetection::Face* inputImageFaces = SeetaFaceDetection::Instance().DetectFaces(inputImage.data, inputImage.cols, inputImage.rows,
		false, false, false, faceCount, duration);

	if (faceCount == 0)
	{
		std::cout << "No faces found in input image!" << std::endl;
		system("pause");
		return;
	}

	cv::Mat inputImageCpy1(inputImage.rows, inputImage.cols, inputImage.channels());
	inputImage.copyTo(inputImageCpy1);
	cv::Rect boundingBox = cv::Rect(inputImageFaces[0].FaceCoordinate.left(), inputImageFaces[0].FaceCoordinate.top(),
		inputImageFaces[0].FaceCoordinate.width(), inputImageFaces[0].FaceCoordinate.height());
	cv::rectangle(inputImageCpy1, boundingBox, cv::Scalar(0, 255, 0), 1, 8, 0);
	cv::imshow("Input image face", inputImageCpy1);

	faceCount = 0;
	duration = 0;
	SeetaFaceDetection::Face* modelImageFaces = SeetaFaceDetection::Instance().DetectFaces(modelImage.data, modelImage.cols, modelImage.rows,
		false, false, false, faceCount, duration);

	if (faceCount == 0)
	{
		std::cout << "No faces found in model image!" << std::endl;
		system("pause");
		return;
	}

	cv::Mat modelImageCpy1(modelImage.rows, modelImage.cols, modelImage.channels());
	modelImage.copyTo(modelImageCpy1);
	boundingBox = cv::Rect(modelImageFaces[0].FaceCoordinate.left(), modelImageFaces[0].FaceCoordinate.top(),
		modelImageFaces[0].FaceCoordinate.width(), modelImageFaces[0].FaceCoordinate.height());
	cv::rectangle(modelImageCpy1, boundingBox, cv::Scalar(0, 255, 0), 1, 8, 0);
	cv::imshow("Model image face", modelImageCpy1);

	FeatureExtraction::Features inputImageFeatures;
	FeatureExtraction::Features modelImageFeatures;

	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::ORB;
	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::ORB;

	FaceAugmentation::Instance().ExtractFacialFeatures(inputImage.data, inputImageFeatures, inputImage.cols,
		inputImage.rows, descriptorType, detectorType, false);

	if (inputImageFeatures.keypointsSize == 0)
	{
		std::cout << "No keypoints found in input image!" << std::endl;
		system("pause");
		return;
	}

	if (inputImageFeatures.descriptorsWidth == 0 || inputImageFeatures.descriptorsHeight == 0 || inputImageFeatures.descriptors.empty())
	{
		std::cout << "No descriptors found in input image!" << std::endl;
		system("pause");
		return;
	}

	std::cout << "Input image facial keypoints: " << inputImageFeatures.keypointsSize << std::endl;
	std::cout << "Input image descriptors size: " << "(" << inputImageFeatures.descriptorsWidth
		<< ", " << inputImageFeatures.descriptorsHeight << ")" << std::endl;

	cv::Mat inputImageCpy2;
	inputImage.copyTo(inputImageCpy2);
	cv::drawKeypoints(inputImageCpy2, inputImageFeatures.keypoints, inputImageCpy2, cv::Scalar(0, 255, 0));
	cv::imshow("Input image keypoints", inputImageCpy2);

	FaceAugmentation::Instance().ExtractFacialFeatures(modelImage.data, modelImageFeatures, modelImage.cols,
		modelImage.rows, descriptorType, detectorType, false);

	if (modelImageFeatures.keypointsSize == 0)
	{
		std::cout << "No keypoints found in model image!" << std::endl;
		system("pause");
		return;
	}

	if (modelImageFeatures.descriptorsWidth == 0 || modelImageFeatures.descriptorsHeight == 0 || modelImageFeatures.descriptors.empty())
	{
		std::cout << "No descriptors found in model image!" << std::endl;
		system("pause");
		return;
	}

	std::cout << "Model image facial keypoints: " << modelImageFeatures.keypointsSize << std::endl;
	std::cout << "Model image descriptors size: " << "(" << modelImageFeatures.descriptorsWidth
		<< ", " << modelImageFeatures.descriptorsHeight << ")" << std::endl;

	cv::Mat modelImageCpy;
	modelImage.copyTo(modelImageCpy);
	cv::drawKeypoints(modelImageCpy, modelImageFeatures.keypoints, modelImageCpy, cv::Scalar(0, 255, 0));
	cv::imshow("Model image keypoints", modelImageCpy);

	FeatureExtraction::DescriptorMatcher descriptorMatcher = FeatureExtraction::DescriptorMatcher::BRUTE_FORCE;

	std::vector<cv::DMatch> matches;
	FeatureExtraction::Instance().Match(inputImageFeatures.descriptors, modelImageFeatures.descriptors, matches, descriptorMatcher);

	std::cout << "Matches: " << matches.size() << std::endl;

	cv::Mat imageMatches;
	cv::drawMatches(inputImage, inputImageFeatures.keypoints, modelImage, modelImageFeatures.keypoints, matches, imageMatches);
	cv::imshow("Matches", imageMatches);

	PoseEstimation::CameraInternals cameraInternals;
	Utility::Instance().ReadCameraParams(cameraInternals, cameraParamsFile);

	if (cameraInternals.A.empty() || cameraInternals.R.empty() || cameraInternals.T.empty())
	{
		std::cout << "Some camera parameter is empty!" << std::endl;
		system("pause");
		return;
	}

	cameraInternals.distCoeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type);

	std::cout << "A" << std::endl << cameraInternals.A << std::endl;
	std::cout << "R" << std::endl << cameraInternals.R << std::endl;
	std::cout << "T" << std::endl << cameraInternals.T << std::endl;
	std::cout << "Dist coeffs" << std::endl << cameraInternals.distCoeffs << std::endl;

	std::vector<cv::Point3d> modelFilePoints;
	Utility::Instance().Read3DPoints(modelFilePoints, modelPointsFile);

	if (modelFilePoints.size() == 0)
	{
		std::cout << "No model 3D points found!" << std::endl;
		system("pause");
		return;
	}

	std::cout << "3D model points: " << modelFilePoints.size() << std::endl;

	std::vector<cv::Point2d> imagePoints;
	std::vector<cv::Point3d> modelPoints;

	FaceAugmentation::Instance().Create2D3DCorrespondences(matches, inputImageFeatures.keypoints, modelFilePoints, imagePoints, modelPoints);

	if (imagePoints.size() == 0 || modelPoints.size() == 0)
	{
		std::cout << "Error to create correspondences." << std::endl;
		system("pause");
		return;
	}

	cv::Mat rotationVector, translationVector;

	PoseEstimation::Instance().EstimateHeadPose(modelPoints, imagePoints, cameraInternals, false, rotationVector, translationVector);

	std::cout << "Rotation" << std::endl << rotationVector << std::endl;
	std::cout << "Translation" << std::endl << translationVector << std::endl;

	std::vector<cv::Point2d> projPoints;
	std::vector<cv::Point3d> endModelPoints;
	
	endModelPoints.push_back(modelPoints.at(0));

	PoseEstimation::Instance().ProjectPoints(endModelPoints, cameraInternals, rotationVector, translationVector, projPoints);

	cv::Mat inputImageCpy3;
	inputImage.copyTo(inputImageCpy3);

	for (int i = 0; i < imagePoints.size(); i++)
		cv::circle(inputImageCpy3, imagePoints[i], 3, cv::Scalar(0, 0, 255), -1);

	cv::line(inputImageCpy3, imagePoints[0], projPoints[0], cv::Scalar(255, 0, 0), 2);
	cv::imshow("Output", inputImageCpy3);

	cv::waitKey(0);
	cv::destroyAllWindows();
	system("pause");
}