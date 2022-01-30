// ���ܣ����� 5-20 ͹����ȱ�ݼ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;
Mat srcImage, srcGary;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
void thresh_callback(int, void*)
{
	Mat srcTemp = srcImage.clone();
	Mat threMat;
	// ����������
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// ��ֵ������
	threshold(srcGary, threMat, thresh, 255, THRESH_BINARY);
	// �������
	findContours(threMat, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	// ͹����ȱ�ݼ�����
	vector<vector<Point> > pointHull(contours.size());
	vector<vector<int> >   intHull(contours.size());
	vector<vector<Vec4i> > hullDefect(contours.size());
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	 Point����͹�����
	//	convexHull(Mat(contours[i]), pointHull[i], false);
	//	 int����͹�����
	//	convexHull(Mat(contours[i]), intHull[i], false);
	//	 ͹��ȱ�ݼ��
	//	convexityDefects(Mat(contours[i]), intHull[i], hullDefect[i]);
	//}
	// ����͹����ȱ�ݼ��
	Mat drawing = Mat::zeros(threMat.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		
		// Point����͹�����
		convexHull(Mat(contours[i]), pointHull[i], false);
		// int����͹�����
		convexHull(Mat(contours[i]), intHull[i], false);
		// ͹��ȱ�ݼ��
		convexityDefects(Mat(contours[i]), intHull[i], hullDefect[i]);
		
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1,
			8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, pointHull, i, color,
			1, 8, vector<Vec4i>(), 0, Point());
		// ����ȱ��
		size_t count = contours[i].size();
		if (count < 300)
			continue;
		// ͹��ȱ�ݵ���������
		vector<Vec4i>::iterator iterDefects = hullDefect[i].begin();
		// �����õ�4��������
		while (iterDefects != hullDefect[i].end()) {
			Vec4i& v = *iterDefects;
			// ��ʼλ��
			int startidx = v[0];
			Point ptStart(contours[i][startidx]);
			// ��ֹλ��
			int endidx = v[1];
			Point ptEnd(contours[i][endidx]);
			// ��͹�ǵ���Զ�ĵ�ȱ��
			int faridx = v[2];
			Point ptFar(contours[i][faridx]);
			// ͹��֮�����Զ��
			int depth = v[3] / 256;
			if (depth > 20 && depth < 80)
			{
				line(drawing, ptStart, ptFar, CV_RGB(0, 255, 0), 2);
				line(drawing, ptEnd, ptFar, CV_RGB(0, 255, 0), 2);
				circle(drawing, ptStart, 4, Scalar(255, 0, 100), 2);
				circle(drawing, ptEnd, 4, Scalar(255, 0, 100), 2);
				circle(drawing, ptFar, 4, Scalar(100, 0, 255), 2);
			}
			iterDefects++;
		}
	}
	cv::imshow("result", drawing);
}
int main()
{
	srcImage = imread("..\\images\\boudingRect.jpg");
	if (!srcImage.data)
		return -1;
	cvtColor(srcImage, srcGary, CV_BGR2GRAY);
	blur(srcGary, srcGary, Size(3, 3));
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, srcImage);
	createTrackbar(" Threshold:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey(0);
	return(0);
}
