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
	//CropAndSaveImageTest();
	ExtractFacialFeaturesTest();

	return 0;
}

void CropAndSaveImageTest()
{
	std::string imageFilename = "../../../Dataset/Images/Faces/0000004.jpg";
	std::string cropFilename = "../../../Dataset/Images/Crop_Faces/crop_0000004.jpg";

	cv::Mat image = cv::imread(imageFilename);
	
	if (image.empty())
	{
		std::cout << "Unable to load input image." << std::endl;
		return;
	}

	std::cout << "Cropping face from \"" << imageFilename << "\"..." << std::endl;

	Utility::Instance().CropAndSaveImage(image.data, image.cols, image.rows, cropFilename);

	std::cout << "Cropped image has been saved in \"" << cropFilename << "\"..." << std::endl;
	std::system("pause");
}

void ExtractFacialFeaturesTest()
{
	bool crop = false;
	// For original image.
	std::string imageFilename = "../../../Dataset/Images/Faces/0000006.jpg";

	// For cropped image.
	//std::string imageFilename = "../../../Dataset/Images/Crop_Faces/crop_0000004.jpg";

	std::cout << "Extracting features from \"" << imageFilename << "\"..." << std::endl;

	cv::Mat image = cv::imread(imageFilename);

	FeatureExtraction::DetectorType detectorType = FeatureExtraction::DetectorType::BRISK;
	FeatureExtraction::DescriptorType descriptorType = FeatureExtraction::DescriptorType::ORB;
	std::string featuresFilename = "features.txt";

	// Call this way if the input image
	// has already been cropped.
	/*FeatureExtraction::Feature feature = Utility::Instance().ExtractFacialFeatures
	(image.data, image.cols, image.rows, false, descriptorType, detectorType, featuresFilename);*/

	// Call this way if a facial cropping
	// was performed before.
	/*FeatureExtraction::Feature feature = Utility::Instance().ExtractFacialFeatures
	(image.data, image.cols, image.rows, false, descriptorType, detectorType, featuresFilename);*/

	FeatureExtraction::Feature feature = Utility::Instance().ExtractFacialFeatures
	(image.data, image.cols, image.rows, descriptorType, detectorType, featuresFilename);


	if (feature.keypointsSize == -1)
	{
		std::cout << "No keypoints found." << std::endl;
		return;
	}

	std::cout << "Features saved in \"" << featuresFilename << "\"." << std::endl;

	cv::Mat displayImage;

	if (crop)
	{
		int faceCount;
		long long duration;
		SeetaFaceDetection::Face* faces = SeetaFaceDetection::Instance().DetectFaces
		(image.data, image.cols, image.rows, false, false, false, faceCount, duration);

		if (faceCount == 0)
		{
			std::cout << "No faces found." << std::endl;
			return;
		}

		displayImage = SeetaFaceDetection::Instance().CropFace(image.data, image.cols, image.rows, faces[0]);
	}
	else
		displayImage = image.clone();
	
	cv::drawKeypoints(displayImage, feature.keypoints, displayImage, cv::Scalar(0, 255, 0));

	cv::imshow("keypoints", displayImage);
	cv::waitKey(0);
	cv::destroyAllWindows();
	std::system("pause");
}