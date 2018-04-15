#include "Utilities.h"

Utility* Utility::instance = NULL;

Utility::Utility() { }

Utility& Utility::Instance()
{
	if (!instance)
	{
		instance = new Utility();
	}

	return *instance;
}

FeatureExtraction::Feature Utility::ExtractFacialFeatures(BYTE* pixels, int width, int height, bool crop, FeatureExtraction::DescriptorType descriptorType, FeatureExtraction::DetectorType detectorType, std::string featuresFilename)
{
	cv::Mat image(height, width, CV_8UC3, pixels);

	if (!image.empty())
	{
		int faceCount;
		long long duration;

		SeetaFaceDetection::Face* faces = SeetaFaceDetection::Instance().DetectFaces(image.data, image.cols, image.rows, false, false, false, faceCount, duration);

		if (faceCount > 0)
		{
			cv::Mat procImage;

			if (crop)
				procImage = SeetaFaceDetection::Instance().CropFace(pixels, width, height, faces[0]);
			else
				procImage = image.clone();

			if (!procImage.empty())
			{
				FeatureExtraction::Feature feature = FeatureExtraction::Instance().ExtractFeatures(procImage.data, procImage.cols, procImage.rows, descriptorType, detectorType);

				if (featuresFilename != "")
				{
					CreateNewFile(featuresFilename);
					SaveFeatures(feature, featuresFilename);
				}

				return feature;
			}
		}
	}

	return {};
}

FeatureExtraction::Feature Utility::ExtractFacialFeatures(BYTE* pixels, int width, int height, FeatureExtraction::DescriptorType descriptorType, FeatureExtraction::DetectorType detectorType, std::string featuresFilename)
{
	cv::Mat image(height, width, CV_8UC3, pixels);

	if (!image.empty())
	{
		int faceCount;
		long long duration;

		SeetaFaceDetection::Face* faces = SeetaFaceDetection::Instance().DetectFaces
		(image.data, image.cols, image.rows, false, false, false, faceCount, duration);

		if (faceCount > 0)
		{

			FeatureExtraction::Feature feature = FeatureExtraction::Instance().ExtractFeatures
			(image.data, image.cols, image.rows, descriptorType, detectorType);

			FeatureExtraction::Feature facialFeature = {};

			for (int i = 0; i < feature.keypointsSize; i++)
			{
				if (feature.keypoints[i].pt.x >= faces[0].FaceCoordinate.left() && feature.keypoints[i].pt.x <= faces[0].FaceCoordinate.right()
					&& feature.keypoints[i].pt.y >= faces[0].FaceCoordinate.top() && feature.keypoints[i].pt.y <= faces[0].FaceCoordinate.bottom())
				{
					facialFeature.keypoints.push_back(feature.keypoints[i]);
					facialFeature.keypointsSize++;
				}					
			}

			if (featuresFilename != "")
			{
				CreateNewFile(featuresFilename);
				SaveFeatures(facialFeature, featuresFilename);
			}

			return facialFeature;
		}
	}

	return {};
}

void Utility::CreateNewFile(std::string filename)
{
	std::fstream fs;

	fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

	if (!fs)
		fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
}

void Utility::SaveFeatures(FeatureExtraction::Feature feature, std::string filename)
{
	std::fstream fs;
	fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

	if (fs.is_open())
	{
		fs << "x y" << std::endl;

		for (int i = 0; i < feature.keypointsSize; i++)
			fs << "" << feature.keypoints[i].pt.x << " " << feature.keypoints[i].pt.y << std::endl;
	}
	fs.close();
}

void Utility::CropAndSaveImage(BYTE* pixels, int width, int height, std::string cropFilename)
{
	cv::Mat image(height, width, CV_8UC3, pixels);

	if (!image.empty())
	{
		int faceCount;
		long long duration;

		SeetaFaceDetection::Face* faces = SeetaFaceDetection::Instance().DetectFaces(image.data, image.cols, image.rows, false, false, false, faceCount, duration);

		if (faceCount > 0)
		{
			cv::Mat crop_image = SeetaFaceDetection::Instance().CropFace(pixels, width, height, faces[0]);
			cv::imwrite(cropFilename, crop_image);
		}
	}
}