#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
void contours_demo(int, void*);
Mat src, dst;
int threshold_value = 100;
int threshold_max = 255;
RNG rng;
const char *output_Win = "output";

int main(int argc, char**argv)
{

	src = imread("F:\\processImage\\PeppersRGB.bmp");
	if (src.empty()) 
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow(output_Win, CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	
	cvtColor(src, src, CV_BGR2GRAY);

	const char *trackbar_title = "threshold value:";
	createTrackbar(trackbar_title, output_Win, &threshold_value, threshold_max, contours_demo);  //阈值自己根据经验定
	contours_demo(0,0);

	cvWaitKey(0);
	return 0; 
}
void contours_demo(int, void*){
	Mat canny_output;
	vector<vector<Point>> contours; //另可以定义多维数组，数组速度比vector快//此定义指一个vector里边装的是轮廓的集合
	vector<Vec4i> hierachy;//拓扑结构图，Vec4i=Vec<int,4>
	Canny(src, canny_output, threshold_value, threshold_value * 2, 3, false);
	findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	
	dst = Mat::zeros(src.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size();i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color,2, 8, hierachy, 0, Point(0, 0));
	}
	imshow(output_Win, dst);
}