#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src;
	src = imread("F:\\processImage\\caisezhixian.png");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}

	Mat gray_src, binImg, temp, dst;
	cvtColor(src, gray_src,CV_BGR2GRAY);
	adaptiveThreshold(~gray_src, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);

	Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
	Mat vline = getStructuringElement(MORPH_RECT, Size(1,src.rows / 16), Point(-1, -1));
	erode(binImg, temp, hline);
	dilate(temp, dst, hline);
	bitwise_not(dst, dst);
	blur(dst, dst, Size(3, 3), Point(-1, -1));

	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	imshow("binImg", binImg);
	imshow("dst", dst);
	cvWaitKey(0);
	return 0;
}