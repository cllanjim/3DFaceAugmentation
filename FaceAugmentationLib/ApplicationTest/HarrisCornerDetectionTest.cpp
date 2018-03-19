/**
*
* This is a test for feature detection task using OpenCV Harris corner detection.
*
* @since 2018-03-17
*/

#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;

const char* source_window = "Source image";
const char* corners_window = "Corners detected";

void cornerHarris_demo(int, void*);

int main()
{
	string src_path = "../../../Images/Faces/0000004.jpg";
	src = imread(src_path, IMREAD_COLOR);

	if (src.empty())
	{
		cout << "Could not open or find image!\n" << endl;
		system("pause");
		return -1;
	}

	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	namedWindow(source_window, WINDOW_NORMAL);
	createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
	imshow(source_window, src);

	cornerHarris_demo(0, 0);

	waitKey(0);
	destroyAllWindows();

	return(0);
}

void cornerHarris_demo(int, void*)
{
	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros(src.size(), CV_32FC1);

	int block_size = 2;
	int aperture_size = 3;
	double k = 0.04;

	cornerHarris(src_gray, dst, block_size, aperture_size, k, BORDER_DEFAULT);

	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);

	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
		}
	}

	namedWindow(corners_window, WINDOW_NORMAL);
	imshow(corners_window, dst_norm_scaled);
}