// ���ܣ����� 8-14 ������ƥ��Ŀ����ȡ
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <flann/miniflann.hpp>
#include <objdetect/objdetect.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

cv::Mat flannMatchExtract(cv::Mat srcImage1, cv::Mat srcImage2)
{
	CV_Assert(srcImage1.data != 0 && srcImage2.data != 0);
	// ����SURF�����
	int hessPara = 300;
	SurfDescriptorExtractor detector(hessPara);
	// �ؼ��㼰����������������
	vector<cv::KeyPoint> kPoint1, kPoint2;
	cv::Mat despMat1, despMat2;
	//��������
	detector.detect(srcImage1, kPoint1);
	detector.detect(srcImage2, kPoint2);
	// ��������ȡ
	SurfDescriptorExtractor extractor;
	extractor.compute(srcImage1, kPoint1, despMat1);
	extractor.compute(srcImage2, kPoint2, despMat2);
	// Flann ������ƥ��
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(despMat1, despMat2, matches);
	double max_dist = 0; double min_dist = 100;
	// �����ж�-����ƥ��� 
	for (int i = 0; i < despMat1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)
			min_dist = dist;
		if (dist > max_dist)
			max_dist = dist;
	}
	printf("Max dist : %f \n", max_dist);
	printf("Min dist : %f \n", min_dist);
	// ���ƥ���
	vector< DMatch > matchVec;
	// ����
	for (int i = 0; i < despMat1.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			matchVec.push_back(matches[i]);
		}
	}
	// ���Ƽ���
	cv::Mat matchMat, matchMat2;
	drawMatches(srcImage1, kPoint1, srcImage2, kPoint2,
		matchVec, matchMat, Scalar::all(-1),
		Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("matchMat", matchMat);
	// ������һ���Լ��
	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < matchVec.size(); i++)
	{
		obj.push_back(kPoint1[matchVec[i].queryIdx].pt);
		scene.push_back(kPoint2[matchVec[i].trainIdx].pt);
	}
	// ���һ����
	Mat H = findHomography(obj, scene, CV_RANSAC);
	// ����任���� 
	Point2f objCorner[4] = { cvPoint(0, 0),
		cvPoint(srcImage1.cols, 0),
		cvPoint(srcImage1.cols, srcImage1.rows),
		cvPoint(0, srcImage1.rows)
	};
	// ����ƥ���
	cv::Point sceneCors[4];
	for (int i = 0; i < 4; i++)
	{
		double x = objCorner[i].x;
		double y = objCorner[i].y;
		// ӳ�������
		double Z = 1. / (H.at<double>(2, 0)*x +
			H.at<double>(2, 1)*y + H.at<double>(2, 2));
		double X = (H.at<double>(0, 0)*x +
			H.at<double>(0, 1)*y + H.at<double>(0, 2))*Z;
		double Y = (H.at<double>(1, 0)*x +
			H.at<double>(1, 1)*y + H.at<double>(1, 2))*Z;
		sceneCors[i] = cvPoint(cvRound(X) +
			srcImage1.cols, cvRound(Y));
	}
	// ����ƥ���Ŀ��   
	line(matchMat, sceneCors[0],
		sceneCors[1], Scalar(0, 255, 0), 2);
	line(matchMat, sceneCors[1],
		sceneCors[2], Scalar(0, 255, 0), 2);
	line(matchMat, sceneCors[2],
		sceneCors[3], Scalar(0, 255, 0), 2);
	line(matchMat, sceneCors[3],
		sceneCors[0], Scalar(0, 255, 0), 2);
	imshow("ObjectMat", matchMat);
	return matchMat;
}
int main()
{
	cv::Mat srcImage1 =
		imread("..\\images\\sAcar.jpg");
	cv::Mat srcImage2 =
		imread("..\\images\\Acar.jpg");
	if (!srcImage1.data || !srcImage2.data)
		return -1;

	cv::Mat resMatchMat = flannMatchExtract(srcImage1, srcImage2);
	cv::waitKey(0);
	return 0;
}
