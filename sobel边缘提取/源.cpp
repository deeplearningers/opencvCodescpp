#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, src_gray, dst, dst1;
	src = imread("F:\\processImage\\LenaRGB.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, src_gray, CV_BGR2GRAY);
	imshow("gray image", src_gray);
	Mat xgrad, ygrad;
	//Sobel(src_gray, xgrad, -1, 1, 0, 3);
	//Sobel(src_gray, ygrad, -1, 0, 1, 3);
	printf("type: \%d\n", src_gray.type());
	Scharr(src_gray, xgrad, -1, 1, 0);
	Scharr(src_gray, ygrad, -1, 0, 1);
	convertScaleAbs(xgrad, xgrad);
	convertScaleAbs(ygrad, ygrad);
	imshow("xgrad", xgrad);
	imshow("ygrad", ygrad);
    //addWeighted(xgrad, 0.5, ygrad, 0.5, 0.0, dst1, -1);
	//×Ô¼ºÐ´
	int width = xgrad.cols;
	int height = ygrad.rows;
	Mat xygrad = Mat(xgrad.size(), xgrad.type());
	for (int row = 0; row < height;row++)
	{
		for (int col = 0; col < width;col++)
		{
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xyg = xg + yg;
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xyg);
		}
	}

	imshow("final image", xygrad);
	 
	cvWaitKey(0);
	return 0;
}