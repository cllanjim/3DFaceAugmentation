/**
*
* This is a test for feature detection task using SURF from OpenCV contrib.
*
* @since 2018-03-17
*/

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

void detect_features(Mat img_1, Mat img_2);
void readme();

/** @function main */
int main(int argc, char** argv)
{
	Mat img_1 = imread("../../../Images/Faces/0000004.jpg", IMREAD_GRAYSCALE);
	Mat img_2 = imread("../../../Images/Faces/0000004.jpg", IMREAD_GRAYSCALE);

	if (!img_1.data || !img_2.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
		exit(0);
	}

	detect_features(img_1, img_2);

	return 0;
}

void detect_features(Mat img_1, Mat img_2)
{
	// Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;

	Ptr<SURF> detector = SURF::create(minHessian);

	std::vector<KeyPoint> keypoints_1, keypoints_2;

	detector->detect(img_1, keypoints_1);
	detector->detect(img_2, keypoints_2);

	// Draw keypoints
	Mat img_keypoints_1; Mat img_keypoints_2;

	drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	// Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1);
	imshow("Keypoints 2", img_keypoints_2);

	waitKey(0);
	destroyAllWindows();
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}