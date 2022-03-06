#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst;
	src = imread("F:\\processImage\\1.jpg");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	char output_title[] = "morphology demo";
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);

	Mat kernel = getStructuringElement(MORPH_RECT,Size(11,11), Point(-1, -1));
	morphologyEx(src, dst, CV_MOP_BLACKHAT, kernel, Point(-1, -1));

	imshow(output_title,dst);

	cvWaitKey(0);
	return 0;
}