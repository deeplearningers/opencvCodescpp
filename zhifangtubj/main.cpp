#include<opencv2\opencv.hpp>
#include<iostream>
#include <math.h>

using namespace std;
using namespace cv;
string convertToString(double d);

int main(int argc, char**argv)
{
	Mat src,test1,test2;
	src = imread("F:\\processImage\\PeppersRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}

	test1 = imread("F:\\processImage\\LenaRGB.bmp");
	test2 = imread("F:\\processImage\\BaboonRGB.bmp");
	//转换到HSV双通道空间
	cvtColor(src, src, CV_BGR2HSV);
	cvtColor(test1, test1, CV_BGR2HSV);
	cvtColor(test2, test2, CV_BGR2HSV);
	
	int h_bins = 50;
	int s_bins = 60; 
	int histSize[] = { h_bins, s_bins };
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };
	const float* ranges[] = { h_ranges, s_ranges };
	int channels[] = { 0, 1 };
	MatND hist_src;
	MatND hist_test1;
	MatND hist_test2; 
	//计算直方图，归一化
	calcHist(&src, 1, channels, Mat(), hist_src, 2, histSize, ranges, true, false);
	calcHist(&test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
	calcHist(&test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
	normalize(hist_src, hist_src, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());
	//直方图比较
	double srcsrc = compareHist(hist_src, hist_src, CV_COMP_CORREL);
	double srctest1 = compareHist(hist_src, hist_test1, CV_COMP_CORREL);
	double srctest2 = compareHist(hist_src, hist_test2, CV_COMP_CORREL);
	double test1test2 = compareHist(hist_test1, hist_test2, CV_COMP_CORREL);
	printf("test1 compare test2 correlation value :%f", test1test2);
	//显示
	putText(src, convertToString(srcsrc), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(test1, convertToString(srctest1), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(test2, convertToString(srctest2), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);

	
	imshow("input", src);
	imshow("test1", test1);
	imshow("test2", test2);
	cvWaitKey(0);
	return 0;
}
string convertToString(double d){
	ostringstream os;    //创建一个流
	if (os << d)         //把值传递到流中
		return os.str();   //获取转换后的字符串并将其返回
	return "invalid conversion";
}