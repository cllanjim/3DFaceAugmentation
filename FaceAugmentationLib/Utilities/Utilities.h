/*
* Description: Functions to be used by all the projects in solution.
* 
* @author João Otávio Brandão (jobal@cin.ufpe.br)
* @since 2018-04-06
*/

#pragma once

#ifdef UTILITIES_EXPORTS  
#define UTILITIES_API __declspec(dllexport)   
#else  
#define UTILITIES_API __declspec(dllimport)   
#endif

#include "SeetaFaceDetection.h"
#include "FeatureExtraction.h"
#include <opencv2\features2d.hpp>
#include "opencv2\xfeatures2d.hpp"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <windows.h>

class Utility
{
public:
	/**
	* Public static singleton instance.
	*/
	static UTILITIES_API Utility& Instance();

	/**
	* Constructor
	*/
	UTILITIES_API Utility();

	/**
	* Extract facial features on a image. The face
	* is detected in this function too. The features
	* are saved in a txt file.
	*
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param crop Flag If true, perform image crop. Otherwise, use the original image.
	* @param descriptorType The OpenCV descriptor type.
	* @param detectorType The OpenCV detector type.
	* @param featuresFilename The output file path that feature info will be save.
	* @return Struct containing extracted feature information.
	*/
	UTILITIES_API FeatureExtraction::Feature ExtractFacialFeatures(BYTE* pixels, int width, int height, bool crop, FeatureExtraction::DescriptorType descriptorType, FeatureExtraction::DetectorType detectorType, std::string featuresFilename);

	/**
	* Extract facial features on a image. The face
	* is detected in this function too. The features
	* are saved in a txt file.
	*
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param descriptorType The OpenCV descriptor type.
	* @param detectorType The OpenCV detector type.
	* @param featuresFilename The output file path that feature info will be save.
	* @return Struct containing extracted feature information.
	*/
	UTILITIES_API FeatureExtraction::Feature ExtractFacialFeatures(BYTE* pixels, int width, int height, FeatureExtraction::DescriptorType descriptorType, FeatureExtraction::DetectorType detectorType, std::string featuresFilename);

	/**
	* Crate a file if it not exists.
	*
	* @param The file path.
	*/
	UTILITIES_API void CreateNewFile(std::string filename);

	/**
	* Store the feature information in a file.
	*
	* @param feature The struct containing feature information.
	* @param filename The output file path.
	*/
	UTILITIES_API void SaveFeatures(FeatureExtraction::Feature feature, std::string filename);

	/**
	* Detect a face in the image, crop it to 256x256
	* size and write it as a new image.
	*
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param cropFilename The destiny path of the cropped image.
	*/
	UTILITIES_API void CropAndSaveImage(BYTE* pixels, int width, int height, std::string cropFilename);

	/**
	* Read 3D points from a text file.
	*
	* @param points3DFilename The input file name that contains the 3D points of the model.
	* @return A vector of 3D points.
	*/
	UTILITIES_API std::vector<cv::Point3d> Read3DPoints(std::string points3DFilename);

	/**
	* Convert features key points to Opencv
	* 2D points.
	*
	* @param keypoints The features key points.
	* @return A vector of 2D points.
	*/
	UTILITIES_API std::vector<cv::Point2d> ParseKeyPointsTo2DPoints(std::vector<cv::KeyPoint> keypoints);

private:
	/**
	* Private static singleton instance.
	*/
	static Utility* instance;

	/**
	* String tokenizer.
	*
	* @param str The string to be splitted.
	* @param c The token.
	* @return A vector of strings.
	*/
	UTILITIES_API std::vector<std::string> Split(const char *str, char c);
};