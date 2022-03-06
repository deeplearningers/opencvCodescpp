#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst, dst1, dst2;
	//int ksize = 0;
	src = imread("F:\\processImage\\BaboonRGB.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	cvtColor(src, src, CV_BGR2GRAY);
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	
	////sobel算子 X方向
	//Mat kernelx = (Mat_<int>(3, 3) << -1, 0, 1, -2,0,2,-1,0,1);
	//filter2D(src, dst, -1, kernelx, Point(-1, -1), 0.0);
	//imshow("X", dst);
	////sobel算子 Y
	//Mat kernely = (Mat_<int>(3, 3) << -1, -2, 0, 0,0,0,1,2,1);
	//filter2D(src, dst1, -1, kernely, Point(-1, -1), 0.0);
	//imshow("Y", dst1);
	////laplas算子--整体的轮廓
	//Mat kernellap = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	//filter2D(src, dst2, -1, kernellap, Point(-1, -1), 0.0);
	//imshow("laplas", dst1);
	int c = 0;
	int index = 0;
	int ksize = 3;

	while (true){
		c = waitKey(1000);
		if ((char)c == 27)//ESC
			break;
		ksize = 4 + (index % 5) * 2 + 1;
		Mat kernel = Mat::ones(Size(ksize,ksize),CV_32F)/(float)(ksize*ksize);//卷积核全是1
		filter2D(src, dst, -1, kernel, Point(-1, -1));
		index++;
		imshow("out", dst);
	}

	cvWaitKey(0);
	return 0;
}