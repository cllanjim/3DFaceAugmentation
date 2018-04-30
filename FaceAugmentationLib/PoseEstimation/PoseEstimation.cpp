#include "PoseEstimation.h"

PoseEstimation* PoseEstimation::instance = NULL;

PoseEstimation::PoseEstimation() { }

PoseEstimation& PoseEstimation::Instance()
{
	if (!instance)
	{
		instance = new PoseEstimation();
	}

	return *instance;
}