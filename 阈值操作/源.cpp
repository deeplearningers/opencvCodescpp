#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src,gray_dst, dst;
int threshold_value = 127;
int threshold_max = 225;
void threshold_Demo(int, void*);

int type_value = 2;
int type_max = 4;

int main(int argc, char**argv)
{
	

	src = imread("F:\\processImage\\PeppersRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	cvtColor(src, gray_dst, CV_BGR2GRAY);
	createTrackbar("threshold value:", "output", &threshold_value, threshold_max, threshold_Demo);
	createTrackbar("type value:", "output", &type_value, type_max, threshold_Demo);
	threshold_Demo(0, 0);
	
	cvWaitKey(0);
	return 0;
}
void threshold_Demo(int, void*){	
	//THRESH_BINARY; THRESH_BINARY_INV;THRESH_TRUNC; THRESH_TOZERO; THRESH_TOZERO_INV; 0-4
	threshold(gray_dst, dst, threshold_value, threshold_max,type_value);
	imshow("output", dst);
}