#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst, dst1;
	src = imread("F:\\processImage\\Cameraman.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}

	//上采样
	pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
	//降采样
	pyrDown(src, dst1, Size(src.cols / 2, src.rows / 2));

	imshow("input", src);
	//imshow("上采样", dst);
	//imshow("降采样", dst1);

	Mat gray_src, g1, g2, dogImage;
	cvtColor(src, gray_src, CV_BGR2GRAY);
	GaussianBlur(gray_src, g1, Size(3, 3), 0, 0);
	GaussianBlur(g1, g2, Size(3, 3), 0, 0);
	subtract(g1, g2, dogImage, Mat());
	normalize(dogImage, dogImage, 255, 0, NORM_MINMAX);
	imshow("g1", g1);
	imshow("g2", g2);
	imshow("dog image", dogImage);

	cvWaitKey(0);
	return 0;
}