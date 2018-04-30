/*
* Description: Head Pose estimation using OpenCV.
*
* @author João Otávio Brandão (jobal@cin.ufpe.br)
* @since 2018-04-30
*/

#pragma once

#ifdef POSEESTIMATION_EXPORTS  
#define POSEESTIMATION_API __declspec(dllexport)   
#else  
#define POSEESTIMATION_API __declspec(dllimport)   
#endif 

#include <windows.h>

class PoseEstimation 
{
public:
	static POSEESTIMATION_API PoseEstimation& Instance();

	/**
	* Constructor
	*/
	POSEESTIMATION_API PoseEstimation();
private:
	static PoseEstimation* instance;
};