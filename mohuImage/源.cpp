#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst, dst1, dst2, dst3;
	src = imread("F:\\processImage\\LenaRGB.bmp");
	if (src.empty())
	{
		cout << "could not load image...\n" << endl;
		return -1;
	}
	blur(src, dst, Size(1, 15), Point(-1, -1));
	GaussianBlur(src, dst1, Size(1, 7),1.5,1.3,4);
	medianBlur(src, dst2, 5);

	bilateralFilter(src, dst3, 50,100, 3);
	Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(dst3, dst3, -1, kernel, Point(-1, -1), 0);
	
	imshow("input", src);
	/*imshow("0output", dst);
	imshow("1output", dst1);
	imshow("2output", dst2);*/
	imshow("3output", dst3);
	cvWaitKey(0);
	return 0;
}