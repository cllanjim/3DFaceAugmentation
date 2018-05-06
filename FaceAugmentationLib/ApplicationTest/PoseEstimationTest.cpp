/**
*
* This is a test for pose estimation purposes.
*
*/
#include "PoseEstimation.h"
#include "Utilities.h"

int main()
{
	std::string points3DFilename = "3D_points.txt";
	Utility::Instance().Read3DPoints(points3DFilename);

	return 0;
}