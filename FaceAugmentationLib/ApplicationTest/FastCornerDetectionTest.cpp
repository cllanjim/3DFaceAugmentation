/**
*
* This is a test for feature detection task using OpenCV FAST corner detection.
*
*/

#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, src_gray;

int main()
{
	string src_path = "../../../Dataset/Images/Faces/0000004.jpg";
	src = imread(src_path, IMREAD_COLOR);

	if (src.empty())
	{
		cout << "Could not open or find image!\n" << endl;
		system("pause");
		return -1;
	}

	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	vector<KeyPoint> keypoints;
	Ptr<FastFeatureDetector> detector = FastFeatureDetector::create();
	vector<Mat> descriptor;

	detector->detect(src_gray, keypoints, Mat());
	drawKeypoints(src_gray, keypoints, src);

	imshow("keypoints", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}