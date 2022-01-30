#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src;
	src = imread("F:\\processImage\\PeppersRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	/*Mat dst;
	dst = Mat(src.size(), src.type());
	dst = Scalar(127, 0, 255);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);*/

	/*Mat dst = src.clone();
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);*/

	/*Mat dst;
	src.copyTo(dst);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);*/
	Mat dst;
	cvtColor(src, dst, CV_BGR2GRAY);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);
	printf("input image channels: %d\n", src.channels());
	printf("output image channels: %d\n", dst.channels());
	
	int cols = dst.cols;
	int rows = dst.rows;
	printf("rows£º%d ;cols: %d\n", rows, cols);
	const uchar* firstRow = dst.ptr<uchar>(0);
	printf("first pixel value:%d\n", *firstRow);

	Mat M(3, 3, CV_8UC3, Scalar(0, 0, 255));
	cout << "M=" <<M<< endl;
	namedWindow("M", CV_WINDOW_AUTOSIZE);
	imshow("M", M);

	Mat M1;
	M1.create(src.size(), src.type());
	M1 = Scalar(0, 255,0);
	imshow("M1", M1);

	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 1);
	//ÑÚÄ£Ä£°å

	Mat m2 = Mat::zeros(src.size(), src.type());
	imshow("m2", m2);

	Mat m3 = Mat::eye(2, 2,CV_8UC1);
	cout << "m3=" << m3 << endl;

	waitKey(0);
	return 0;
}