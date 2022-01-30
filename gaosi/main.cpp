#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src;
	src = imread("F:\\calibration\\20180611\\CalibFolder_NEXK0019\\depth\\depth891011\\cap_00000000_L.bmp");
	
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	imwrite("cap_00000000_L.bmp", src);
		
	cvWaitKey(0);
	return 0;
}