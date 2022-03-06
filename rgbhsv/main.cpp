// ���ܣ����� 2-31 RGB ת HSV
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
int main()
{
	// ͼ��Դ��ȡ���ж�
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat image_hsv, image_H, image_S, image_V, image_col;
	// HSV��ɫ�ռ�ת��
	cv::cvtColor(srcImage, image_hsv, CV_BGR2HSV);
	cv::imshow("image_hsv", image_hsv);
	// YCrCb��ɫ�ռ�ת��
	cv::cvtColor(srcImage, image_col, CV_BGR2YCrCb);
	cv::imshow("image_YCrCb", image_col);
	// HLS��ɫ�ռ�ת��
	cv::cvtColor(srcImage, image_col, CV_BGR2HLS);
	cv::imshow("image_HLS", image_hsv);
	// Lab��ɫ�ռ�ת��
	cv::cvtColor(srcImage, image_col, CV_BGR2Lab);
	cv::imshow("image_Lab", image_col);
	// ����HSV����ͨ��
	std::vector<cv::Mat> hsvChannels;
	cv::split(image_hsv, hsvChannels);
	// 0ͨ��ΪH������1ͨ��ΪS������2ͨ��ΪV����
	image_H = hsvChannels[0];
	image_S = hsvChannels[1];
	image_V = hsvChannels[2];
	// �ֱ���ʾ��ͨ��ͼ��
	cv::imshow("image_H", image_H);
	cv::imshow("image_S", image_S);
	cv::imshow("image_V", image_V);
	cv::waitKey(0);
	return 0;
}
