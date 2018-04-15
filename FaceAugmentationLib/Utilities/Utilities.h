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
	static UTILITIES_API Utility& Instance();

	/**
	* Constructor
	*/
	UTILITIES_API Utility();

	/**
	* Extract features from a face image. The face
	* is detected in this function too. The features
	* are saved in a txt file.
	*
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param descriptorType The OpenCV descriptor type.
	* @param detectorType The OpenCV detector type.
	* @param feat_file_path The output file path that feature info will be save.
	* @return Struct containing extracted feature information.
	*/
	UTILITIES_API FeatureExtraction::Feature ExtractFaceFeatures(BYTE* pixels, int width, int height, FeatureExtraction::DescriptorType descriptorType, FeatureExtraction::DetectorType detectorType, std::string feat_file_path);

	/**
	* Crate a file if it not exists.
	*
	* @param The file path.
	*/
	UTILITIES_API void CreateNewFile(std::string file_path);

	/**
	* Store the feature information in a file.
	*
	* @param feature The struct containing feature information.
	* @param file_path The output file path.
	*/
	UTILITIES_API void SaveFeatures(FeatureExtraction::Feature feature, std::string file_path);

private:
	static Utility* instance;
};