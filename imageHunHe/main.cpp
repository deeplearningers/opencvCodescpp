#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src1, src2, dst, dst2;
	src1 = imread("F:\\processImage\\PeppersRGB.tif");
	src2 = imread("F:\\processImage\\LenaRGB.tif");
	if (src1.empty()&&src2.empty()){
		cout << "could not load image!" << endl;
		return -1;
	}
	
	double alpha = 0.5;
	if (src1.rows == src2.rows && src1.cols == src2.cols && src1.type() == src2.type())
	{
		addWeighted(src1, alpha, src2, (1.0 - alpha), 0.0, dst);
		multiply(src1, src2, dst2,1.0);
	}
	else{
		printf("could not blend image,the size of images are not same.\n");
	}

	imshow("input1", src1);
	imshow("input2", src2);
	imshow("output", dst);
	imshow("output1", dst2);

	cvWaitKey(0);
	return 0;
}