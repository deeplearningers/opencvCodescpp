#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src;
	src = imread("F:\\processImage\\1.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("edges", CV_WINDOW_AUTOSIZE);
	namedWindow("hough", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat src_gray, dst, dst1;
	Canny(src, src_gray, 100, 150,3);
    //cvtColor(src_gray, dst, CV_BGR2GRAY);
	imshow("edges", src_gray);

	vector<Vec4f> plines;
	HoughLinesP(src_gray, plines, 1, CV_PI / 180, 10, 0, 10);
	Scalar color = Scalar(0, 0, 255);
	for (size_t i = 0; i < plines.size(); i++)
	{
		Vec4f hline = plines[i];
		line(dst1, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA);
	}
	imshow("hough", dst1);



	cvWaitKey(0);
	return 0;
}