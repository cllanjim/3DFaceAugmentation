/**
*
* This is a test for the utilities functions.
*
*/
#include "Utilities.h"

void CropAndSaveImageTest();
void ExtractFacialFeaturesTest();

int main()
{
	CropAndSaveImageTest();
	ExtractFacialFeaturesTest();

	return 0;
}

void CropAndSaveImageTest()
{
	std::string image_path = "../../../Dataset/Images/Faces/0000004.jpg";
	std::string cropped_image_path = "../../../Dataset/Images/Crop_Faces/crop_0000004.jpg";

	cv::Mat image = cv::imread(image_path);
	
	if (image.empty())
	{
		std::cout << "Unable to load input image." << std::endl;
		return;
	}

	std::cout << "Cropping face from \"" << image_path << "\"..." << std::endl;

	Utility::Instance().CropAndSaveImage(image.data, image.cols, image.rows, cropped_image_path);

	std::cout << "Cropped image has been saved in \"" << cropped_image_path << "\"..." << std::endl;
	std::system("pause");
}

void ExtractFacialFeaturesTest()
{
	// For original image.
	/*std::string image_path = "../../../Dataset/Images/Faces/0000004.jpg";*/

	// For cropped image.
	std::string image_path = "../../../Dataset/Images/Crop_Faces/crop_0000004.jpg";

	std::cout << "Extracting features from \"" << image_path << "\"..." << std::endl;

	cv::Mat image = cv::imread(image_path);

	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::ORB;
	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::ORB;
	std::string feat_file_path = "features.txt";

	// Call this way to if the input image
	// has already been cropped.
	FeatureExtraction::Feature feature = Utility::Instance().ExtractFacialFeatures
	(image.data, image.cols, image.rows, false, descriptorType, detectorType, feat_file_path);

	// Call this way to perform face crop before
	// extracting the features.
	/*FeatureExtraction::Feature feature = Utility::Instance().ExtractFacialFeatures
	(image.data, image.cols, image.rows, true, descriptorType, detectorType, feat_file_path);*/

	if (feature.keypointsSize == -1)
	{
		std::cout << "No keypoints found." << std::endl;
		return;
	}

	std::cout << "Features saved in \"" << feat_file_path << "\"." << std::endl;

	int faceCount;
	long long duration;
	SeetaFaceDetection::Face* faces = SeetaFaceDetection::Instance().DetectFaces
	(image.data, image.cols, image.rows, false, false, false, faceCount, duration);

	if (faceCount == 0) 
	{
		std::cout << "No faces found." << std::endl;
		return;
	}

	cv::Mat cropped_face = SeetaFaceDetection::Instance().CropFace(image.data, image.cols, image.rows, faces[0]);

	cv::drawKeypoints(cropped_face, feature.keypoints, cropped_face, cv::Scalar(0, 255, 0));

	cv::imshow("keypoints", cropped_face);
	cv::waitKey(0);
	cv::destroyAllWindows();
	std::system("pause");
}