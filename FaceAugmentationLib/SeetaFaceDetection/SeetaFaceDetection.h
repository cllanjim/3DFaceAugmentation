/* Voxar Labs, Samsung Electronics
*
* Copyright(c) 2016 by Samsung Electronics
*
* This software is the confidential and proprietary information
* of Samsung Electronics, Inc. ("Confidential Information"). You
* shall not disclose such Confidential Information and shall use
* it only in accordance with the terms of the license agreement
* you entered into with Samsung.
*
* Description: Face detection using SeetaFace.
*
* @author João Paulo Lima (jpsml@cin.ufpe.br)
* @since 2016-10-26
*/

#pragma once

#ifdef SEETAFACEDETECTION_EXPORTS  
#define SEETAFACEDETECTION_API __declspec(dllexport)   
#else  
#define SEETAFACEDETECTION_API __declspec(dllimport)   
#endif 

#include <dlib\geometry.h>
#include <face_detection.h>
#include <face_alignment.h>
#include <opencv2/opencv.hpp>
#include <windows.h>

class SeetaFaceDetection
{
public:

	struct Face
	{
	public:
		dlib::rectangle FaceCoordinate;
		dlib::rectangle EyesCoordinate;
		dlib::rectangle SmileCoordinate;
		int openEyesCount = 0;
		int closedEyesCount = 0;
		int smilesCount = 0;
		double score = 0;

		Face() {}

		Face(dlib::rectangle face)
		{
			FaceCoordinate = face;
		}
	};

	static SEETAFACEDETECTION_API SeetaFaceDetection& Instance();
	SEETAFACEDETECTION_API SeetaFaceDetection();
	SEETAFACEDETECTION_API Face* DetectFaces(BYTE* pixels, int width, int height, bool detectEyes, bool detectSmile, bool writeLog, int& facecount, long long& duration);

private:
	static SeetaFaceDetection* instance;
	seeta::FaceDetection faceDetector;
	seeta::FaceAlignment landmarkDetector;
	cv::CascadeClassifier openEyeCascade;
	cv::CascadeClassifier smileCascade;
};
