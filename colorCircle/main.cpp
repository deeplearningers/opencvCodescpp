// ���ܣ����� 5-28 ��ɫԲ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <vector>
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\circle.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat resultImage = srcImage.clone();
	// ��ֵ�˲�
	cv::medianBlur(srcImage, srcImage, 3);
	// ת����hsv��ɫ�ռ�
	cv::Mat hsvImage;
	cv::cvtColor(srcImage, hsvImage, cv::COLOR_BGR2HSV);
	cv::imshow("hsvImage", hsvImage);
	// ��ɫ��ֵ������
	cv::Mat lowTempMat;
	cv::Mat upperTempMat;
	// ����ֵ�޶�
	cv::inRange(hsvImage, cv::Scalar(0, 100, 100),
		cv::Scalar(10, 255, 255), lowTempMat);
	// ����ֵ�޶�
	cv::inRange(hsvImage, cv::Scalar(160, 100, 100),
		cv::Scalar(179, 255, 255), upperTempMat);
	cv::imshow("lowTempMat", lowTempMat);
	cv::imshow("upperTempMat", upperTempMat);
	// ��ɫ��ֵ�޶��ϲ�
	cv::Mat redTempMat;
	cv::addWeighted(lowTempMat, 1.0, upperTempMat,
		1.0, 0.0, redTempMat);
	// ��˹ƽ��
	cv::GaussianBlur(redTempMat, redTempMat, cv::Size(9, 9), 2, 2);
	// ����任
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(redTempMat, circles, CV_HOUGH_GRADIENT,
		1, redTempMat.rows / 8, 100, 20, 0, 0);
	// ��ɫԲ������ж�
	if (circles.size() == 0)
		return 1;
	for (int i = 0; i < circles.size(); ++i)
	{
		// ���Ƽ�⵽��ɫԲ
		cv::Point center(round(circles[i][0]), round(circles[i][1]));
		int radius = round(circles[i][2]);
		cv::circle(resultImage, center, radius,
			cv::Scalar(0, 255, 0), 5);
	}
	cv::imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
