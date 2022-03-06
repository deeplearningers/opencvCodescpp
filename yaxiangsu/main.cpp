#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi CornorDetect"

Mat src, gray;
vector<Point2f> corners;//声明为全局变量否则报错，圆心坐标
int maxCornerNum = 10;
int maxTrackbarNum = 300;


//滚动条回调函数
void cornersRefinement(int, void*){
	Mat copy = src.clone();
	if (maxCornerNum <= 1){
		maxCornerNum = 1;
	}
	//角点检测参数准备
	
	double qualityLevel = 0.2;//角点检测可接受的最小特征值0.01
	double minDistance = 10;//角点之间的最小距离
	int blockSize = 3;//计算导数自相关矩阵时的指定的领域范围
	double k = 0.04;//权重系数

	//进行Shi-Tomasi角点检测
	goodFeaturesToTrack(gray,
		corners,
		maxCornerNum,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		false,
		k);
	//像素级角点使用蓝色圆圈绘制
	for (int i = 0; i <maxCornerNum; i++){
		circle(copy, corners[i], 8, Scalar(255, 0, 0), 2, 8, 0);
	}

	/// 角点位置精准化参数
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	//迭代的终止条件
	TermCriteria criteria = TermCriteria(
		CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,
		40, //maxCount=40
		0.001);    //epsilon=0.001
	/// 计算精准化后的角点位置
	cornerSubPix(gray, corners, winSize, zeroZone, criteria);
	//亚像素级角点使用品红色圆圈绘制
	for (int i = 0; i < maxCornerNum; i++){
		circle(copy, corners[i], 4, Scalar(255, 0, 255), 2, 8, 0);
		// 输出角点坐标  
		cout << " [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	}
	cout << endl;
	imshow(WINDOW_NAME, copy);
	
}

int main(){
	src = imread("Goldhill.bmp", 1);
	cvtColor(src, gray, CV_BGR2GRAY);
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, src);
	
	createTrackbar("MaxNofCornor:", WINDOW_NAME, &maxCornerNum, maxTrackbarNum, cornersRefinement);
	cornersRefinement(0, 0);


	cvWaitKey(0);
	return 0;
}