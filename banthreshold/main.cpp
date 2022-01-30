// ���ܣ����� 3-5 ����ֵ����ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream> 
using namespace std;
using namespace cv;
int main()
{
	// ��ȡԴͼ���ж�
	cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
	if (!srcImage.data)
		return 1;
	// ת��Ϊ�Ҷ�ͼ��
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::imshow("srcGray", srcGray);
	// ��ʼ����ֵ����
	const int maxVal = 255;
	int thresholdVal = 125;
	cv::Mat dstTempImage, dstImage;
	// ��ֵ��Դ�Ҷ�ͼ�������ֵ������
	cv::threshold(srcGray, dstTempImage,
		thresholdVal, 255, cv::THRESH_BINARY);
	// ����������õ���ֵ�����
	cv::bitwise_and(srcGray, dstTempImage, dstImage);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
