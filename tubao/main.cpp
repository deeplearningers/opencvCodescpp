#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
Mat src, src_gray,dst;
const char* output_win = "output";
RNG rng(12345);
int threshold_value = 100;
int threshold_max = 255;
void threshold_callback(int,void*);

int main(int argc, char**argv)
{

	src = imread("F:\\processImage\\fish.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);

	createTrackbar("threshold:", "input", &threshold_value, threshold_max, threshold_callback);
	threshold_callback(0,0);

	cvWaitKey(0);
	return 0;
}
void threshold_callback(int, void*){
	Mat dst,dst1;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	threshold(src_gray, dst, threshold_value, threshold_max, THRESH_BINARY);
	findContours(dst, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>> convex(contours.size());
	for (size_t i = 0; i < contours.size();i++)
	{
		convexHull(contours[i], convex[i], false, true); //false-逆时针方向
	}
	//绘制
	dst1 = Mat::zeros(src.size(), CV_8UC3);
	for (size_t k = 0; k < contours.size();k++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst1, contours, k, color, 2, 8, hierachy);
		drawContours(dst1, convex, k, color, 2, 8, Mat(), 0, Point(0, 0));
	}
	imshow(output_win, dst1);
	return;
}