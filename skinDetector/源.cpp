// ���ܣ����� 7-8 ��ɫ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��//
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>   
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
#include <vector>     
int main()
{
	cv::Mat srcImage, resultMat;
	srcImage = cv::imread("..\\images\\hand1.jpg");
	if (srcImage.empty())
		return -1;
	// ������Բģ��   
	cv::Mat skinMat = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);
	ellipse(skinMat, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
		43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);
	// �ṹԪ�ض���
	cv::Mat struElmen = getStructuringElement(cv::MORPH_RECT,
		cv::Size(3, 3), cv::Point(-1, -1));
	cv::Mat YcrcbMat;
	cv::Mat tempMat = cv::Mat::zeros(srcImage.size(), CV_8UC1);
	// ��ɫ�ռ�ת��YCrCb
	cvtColor(srcImage, YcrcbMat, CV_BGR2YCrCb);
	// ��ԲƤ��ģ�ͼ��
	for (int i = 0; i < srcImage.rows; i++)
	{
		uchar* p = (uchar*)tempMat.ptr<uchar>(i);
		cv::Vec3b* ycrcb = (cv::Vec3b*)YcrcbMat.ptr<cv::Vec3b>(i);
		for (int j = 0; j < srcImage.cols; j++)
		{
			// ��ɫ�ж�
			if (skinMat.at<uchar>(ycrcb[j][1], ycrcb[j][2]) > 0)
				p[j] = 255;
		}
	}
	// ��̬ѧ�ղ���     
	morphologyEx(tempMat, tempMat, cv::MORPH_CLOSE, struElmen);
	// ������������
	std::vector< std::vector<cv::Point> > contours;
	std::vector< std::vector<cv::Point> > resContours;
	std::vector< cv::Vec4i > hierarchy;
	// ��ͨ�����
	findContours(tempMat, contours, hierarchy,
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	// ɸѡα����   
	for (size_t i = 0; i < contours.size(); i++)
	{
		if (fabs(contourArea(cv::Mat(contours[i]))) > 1000)
			resContours.push_back(contours[i]);
	}
	tempMat.setTo(0);
	// ��������
	drawContours(tempMat, resContours, -1,
		cv::Scalar(255, 0, 0), CV_FILLED);
	srcImage.copyTo(resultMat, tempMat);
	imshow("srcImage", srcImage);
	imshow("resultMat", resultMat);
	cv::waitKey(0);
	return 0;
}
