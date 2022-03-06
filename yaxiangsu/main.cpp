#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi CornorDetect"

Mat src, gray;
vector<Point2f> corners;//����Ϊȫ�ֱ������򱨴�Բ������
int maxCornerNum = 10;
int maxTrackbarNum = 300;


//�������ص�����
void cornersRefinement(int, void*){
	Mat copy = src.clone();
	if (maxCornerNum <= 1){
		maxCornerNum = 1;
	}
	//�ǵ������׼��
	
	double qualityLevel = 0.2;//�ǵ���ɽ��ܵ���С����ֵ0.01
	double minDistance = 10;//�ǵ�֮�����С����
	int blockSize = 3;//���㵼������ؾ���ʱ��ָ��������Χ
	double k = 0.04;//Ȩ��ϵ��

	//����Shi-Tomasi�ǵ���
	goodFeaturesToTrack(gray,
		corners,
		maxCornerNum,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		false,
		k);
	//���ؼ��ǵ�ʹ����ɫԲȦ����
	for (int i = 0; i <maxCornerNum; i++){
		circle(copy, corners[i], 8, Scalar(255, 0, 0), 2, 8, 0);
	}

	/// �ǵ�λ�þ�׼������
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	//��������ֹ����
	TermCriteria criteria = TermCriteria(
		CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,
		40, //maxCount=40
		0.001);    //epsilon=0.001
	/// ���㾫׼����Ľǵ�λ��
	cornerSubPix(gray, corners, winSize, zeroZone, criteria);
	//�����ؼ��ǵ�ʹ��Ʒ��ɫԲȦ����
	for (int i = 0; i < maxCornerNum; i++){
		circle(copy, corners[i], 4, Scalar(255, 0, 255), 2, 8, 0);
		// ����ǵ�����  
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