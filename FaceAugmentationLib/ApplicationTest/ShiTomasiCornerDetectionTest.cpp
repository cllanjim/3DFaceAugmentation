/**
*
* This is a test for feature detection task using OpenCV Shi-Tomasi corner detection.
*
* @since 2018-03-17
*/

#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;

int maxCorners = 23;
int maxTrackbar = 100;

RNG rng(12345);
const char* source_window = "Image";

/// Function header
void goodFeaturesToTrack_Demo(int, void*);

/**
 * @function main
 */
int main()
{
	string str_path = "../../../Images/Faces/0000004.jpg";
	/// Load source image and convert it to gray
	src = imread(str_path, 1);
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create Window
	namedWindow(source_window, CV_WINDOW_NORMAL);

	/// Create Trackbar to set the number of corners
	createTrackbar("Max  corners:", source_window, &maxCorners, maxTrackbar, goodFeaturesToTrack_Demo);

	imshow(source_window, src);

	goodFeaturesToTrack_Demo(0, 0);

	waitKey(0);
	return(0);
}

/**
* @function goodFeaturesToTrack_Demo.cpp
* @brief Apply Shi-Tomasi corner detector
*/
void goodFeaturesToTrack_Demo(int, void*)
{
	if (maxCorners < 1)
		maxCorners = 1;

	/// Parameters for Shi-Tomasi algorithm
	vector<Point2f> corners;
	double quality_level = 0.01;
	double min_distance = 10;
	int block_size = 3;
	bool use_harris_detector = false;
	double k = 0.04;

	/// Copy the source image
	Mat copy;
	copy = src.clone();

	// Apply corner detection
	goodFeaturesToTrack(src_gray, corners, maxCorners, quality_level, min_distance, Mat(), block_size, use_harris_detector, k);

	/// Draw corners detected
	cout << "** Number of corners detected: " << corners.size() << endl;

	int r = 4;
	for (int i = 0; i < corners.size(); i++)
		circle(copy, corners[i], r, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);

	/// Show what you got
	namedWindow(source_window, CV_WINDOW_NORMAL);
	imshow(source_window, copy);
}