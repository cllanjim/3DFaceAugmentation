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
* @author João Otávio Brandão (jobal@cin.ufpe.br)
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
#include <face_identification.h>
#include <opencv2\opencv.hpp>
#include <chrono>
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

	/**
	* Crop a face image based on the face landmarks. 
	* The image is resized to 256x256 pixels.
	*
	* @param pixels The image data.
	* @param width The image width.
	* @param height The image height.
	* @param face The face detected previously. Contains the face bounding box information.
	* @return Cropped image.
	*/
	SEETAFACEDETECTION_API cv::Mat CropFace(BYTE* pixels, int width, int height, Face face);

private:
	static SeetaFaceDetection* instance;
	seeta::FaceDetection faceDetector;
	seeta::FaceAlignment landmarkDetector;
	seeta::FaceIdentification faceRecognizer;
	cv::CascadeClassifier openEyeCascade;
	cv::CascadeClassifier smileCascade;
};
