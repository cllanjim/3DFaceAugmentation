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
#include "PoseEstimation.h"
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

	UTILITIES_API void SaveKeypoints(std::vector<cv::KeyPoint> keypoints, std::string file);

	/**
	* Crates a file if it not exists.
	*
	* @param The file path.
	*/
	UTILITIES_API void CreateNewFile(std::string file);

	/**
	* Reads 3D points from a text file.
	*
	* @param points3DFilename The input file name that contains the 3D points of the model.
	* @return A vector of 3D points.
	*/
	UTILITIES_API void Read3DPoints(std::vector<cv::Point3d> &points, std::string file);

	UTILITIES_API void ReadCameraParams(PoseEstimation::CameraInternals &cameraInternals, std::string file);

	///**
	//* Stores the feature information in a file.
	//*
	//* @param feature The struct containing feature information.
	//* @param filename The output file path.
	//*/
	//UTILITIES_API void SaveFeatures(FeatureExtraction::Features feature, std::string filename);

	///**
	//* Detects a face in the image, crop it to 256x256
	//* size and write it as a new image.
	//*
	//* @param pixels The image data.
	//* @param width The image width.
	//* @param height The image height.
	//* @param cropFilename The destiny path of the cropped image.
	//*/
	//UTILITIES_API void CropAndSaveImage(BYTE* pixels, int width, int height, std::string cropFilename);

	///**
	//* Converts features key points to Opencv
	//* 2D points.
	//*
	//* @param keypoints The features key points.
	//* @return A vector of 2D points.
	//*/
	//UTILITIES_API std::vector<cv::Point2d> ParseKeyPointsTo2DPoints(std::vector<cv::KeyPoint> keypoints);

	//UTILITIES_API void DrawLines(std::vector<cv::Point2d> imagePoints, std::vector<cv::Point2d> projPoints, cv::Mat &outputImage);

	//

private:
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