#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src;
	src = imread("F:\\processImage\\LenaRGB.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat gray_src, dst,laplance_img;
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray_src, CV_BGR2GRAY);
	Laplacian(gray_src, laplance_img, CV_16S, 1, 1, 0);
	convertScaleAbs(laplance_img, laplance_img);
	threshold(laplance_img, laplance_img, 0, 255,THRESH_OTSU);
	imshow("laplance image", laplance_img);

	cvWaitKey(0);
	return 0;
}