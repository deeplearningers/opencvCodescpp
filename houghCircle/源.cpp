// ���ܣ����� 5-18 ����Բ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/opencv.hpp>
#include<vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	cv::Mat srcImage = imread("..\\images\\circle.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	// ת��Ϊ�Ҷ�ͼ��
	cv::Mat src_gray;
	cvtColor(srcImage, src_gray, CV_BGR2GRAY);
	// ��˹ƽ���˲�
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);
     vector<Vec3f> circles;
	// ����Բ���
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT,
		1, src_gray.rows / 10, 200, 100, 0, 0);
	// ���õ��Ľ����ͼ
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// ���Բ����
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// ���Բ����
		circle(srcImage, center, radius, Scalar(120, 120, 120), 3, 8, 0);
	}
	cv::imshow("HoughResult", srcImage);
	cv::waitKey(0);
	return 0;
}
