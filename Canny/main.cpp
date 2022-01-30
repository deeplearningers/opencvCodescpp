#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
int t1_value = 50;
int max_value = 255;
Mat src, dst, gray_src;

void Canny_Demo(int, void*);

int main(int argc, char**argv)
{
	
	src = imread("F:\\processImage\\LenaRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("Canny Result", CV_WINDOW_AUTOSIZE);//²»¿ÉÉÙ
	imshow("input", src);

	cvtColor(src, gray_src, CV_BGR2GRAY);
	createTrackbar("threshold value:", "Canny Result", &t1_value, max_value, Canny_Demo);
	Canny_Demo(0, 0);

	waitKey(0);
	return 0;
}
void Canny_Demo(int, void*)
{
	Mat edge_output;
	blur(gray_src, gray_src, Size(3, 3), Point(-1, -1),BORDER_DEFAULT);
	Canny(gray_src, edge_output, t1_value, t1_value * 3, 3, false);

	dst.create(src.size(), src.type());
	src.copyTo(dst, edge_output);
	imshow("Canny Result", dst);
}