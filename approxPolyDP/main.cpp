// ���ܣ����� 5-21 ��С������Բ����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 5-22 �����߽������Բ
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
#include <stdio.h>
using namespace cv;
using namespace std;
// ������Ӿ�����Բ����
void  cacBounding(cv::Mat src)
{
	RNG rng(12345);
	Mat threMat;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// ��ֵ������
	threshold(src, threMat, 120, 255, THRESH_BINARY);
	cv::imshow("threMat", threMat);
	// ����߽�����
	findContours(threMat, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	// ����αƽ�����,��ȡ���κ�Բ�α߽��
	vector<vector<Point> > conPoint(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		// ����ν���
		approxPolyDP(Mat(contours[i]), conPoint[i], 3, true);
		// ��С��Ӿ��μ���
		boundRect[i] = boundingRect(Mat(conPoint[i]));
		// ��С���Բ����
		minEnclosingCircle(conPoint[i], center[i], radius[i]);
	}
	// ��ͼ��ʾ
	Mat resultMat = Mat::zeros(threMat.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		// ���������ɫ
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		// ���ƶ��������
		drawContours(resultMat, conPoint, i, color,
			1, 8, vector<Vec4i>(), 0, Point());
		// ���ƶ���ΰ�Χ�ľ��ο�
		rectangle(resultMat, boundRect[i].tl(),
			boundRect[i].br(), color, 2, 8, 0);
		
		// ���ƶ����Բ�ο�
		circle(resultMat, center[i], (int)radius[i],
			color, 2, 8, 0);
	}
	cv::imshow("boundRectResult", resultMat);
}
// �������б��Ӿ�����Բ����
void  cacBoundRectRandomDirection(cv::Mat src)
{
	RNG rng(12345);
	Mat threMat;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//  ��ֵ������
	threshold(src, threMat, 120, 255, THRESH_BINARY);
	// ����߽�����
	findContours(threMat, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	// ��ÿ���ҵ���������������б�ı߽�����Բ
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		// ������С�������
		minRect[i] = minAreaRect(Mat(contours[i]));
		// �������������Բ
		if (contours[i].size() > 5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}
	// ��������������б�ı߽��ͱ߽���Բ
	Mat resultMat = Mat::zeros(threMat.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		// ���������ɫ
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		// �߽���������
		drawContours(resultMat, contours, i, color, 1, 8,
			vector<Vec4i>(), 0, Point());
		// ���Ʊ߽���Բ
		ellipse(resultMat, minEllipse[i], color, 2, 8);
		// ���Ʊ߽����
		Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(resultMat, rect_points[j], rect_points[(j + 1) %
			4], color, 1, 8);
	}
	imshow("resultMat", resultMat);
}
int main()
{
	cv::Mat srcImage = imread("..\\images\\boudingRect.jpg");
	if (!srcImage.data)
		return -1;
	// ת���ɻҶ�ͼ�񲢽���ƽ��
	cv::Mat srcGray, blurMat;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	blur(srcGray, blurMat, Size(3, 3));
	// cv::imshow( "blurMat", blurMat );
	// ������Ӿ�����Բ����
	cacBoundRectRandomDirection(blurMat);
	// �������б��Ӿ�����Բ����
	cacBounding(blurMat);
	cv::imshow("srcImage", srcImage);
	cv::waitKey(0);
	return(0);
}
