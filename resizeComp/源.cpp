// ���ܣ����� 4-3 resize ��ֵ�������ܶԱ�
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
using namespace cv;
void ResizeExample(cv::Mat srcImage)
{
	CV_Assert(srcImage.data != NULL);
	cv::imshow("srcImage", srcImage);
	cv::Mat dstImage(156, 156, CV_8UC3);
	// ����1 Ĭ�ϲ��� ˫���Բ�ֵ
	double tTime;
	tTime = (double)getTickCount();
	const int nTimes = 100;
	for (int i = 0; i < nTimes; i++)
	{
		resize(srcImage, dstImage, dstImage.size(), 0, 0);
	}
	tTime = 1000 * ((double)getTickCount() - tTime) /
		getTickFrequency();
	tTime /= nTimes;
	std::cout << "˫���Բ�ֵ: " << tTime << std::endl;
	cv::imshow("1 default parameters:dstImage", dstImage);
	// ����2 ����ڲ�ֵ 
	tTime = (double)getTickCount();
	for (int i = 0; i < nTimes; i++)
	{
		resize(srcImage, dstImage, cv::Size(156, 156), 0, 0,
			cv::INTER_NEAREST);
	}
	tTime = 1000 * ((double)getTickCount() - tTime) /
		getTickFrequency();
	tTime /= nTimes;
	std::cout << "����ڲ�ֵ: " << tTime << std::endl;
	cv::imshow("2 INTER_NEAREST:dstImage", dstImage);
	// ����3 ���������ֵ 
	tTime = (double)getTickCount();
	for (int i = 0; i < nTimes; i++)
	{
		resize(srcImage, dstImage, cv::Size(156, 156), 0.5, 0.5,
			cv::INTER_AREA);
	}
	tTime = 1000 * ((double)getTickCount() - tTime) /
		getTickFrequency();
	tTime /= nTimes;
	std::cout << "���������ֵ: " << tTime << std::endl;
	cv::imshow("3 INTER_AREA:dstImage", dstImage);
	// ����4 ���β�ֵ 
	tTime = (double)getTickCount();
	for (int i = 0; i < nTimes; i++)
	{
		resize(srcImage, dstImage, cv::Size(), 0.5, 0.5,
			cv::INTER_CUBIC);
	}
	tTime = 1000 * ((double)getTickCount() - tTime) /
		getTickFrequency();
	tTime /= nTimes;
	std::cout << "���β�ֵ: " << tTime << std::endl;
	cv::imshow("4 INTER_CUBIC", dstImage);
	// ����5 ����˹��ֵ 
	tTime = (double)getTickCount();
	for (int i = 0; i < nTimes; i++)
	{
		resize(srcImage, dstImage, cv::Size(), 0.5, 0.5,
			cv::INTER_LANCZOS4);
	}
	tTime = 1000 * ((double)getTickCount() - tTime) /
		getTickFrequency();
	tTime /= nTimes;
	std::cout << "����˹��ֵ: " << tTime << std::endl;
	cv::imshow("5 INTER_LANCZOS4", dstImage);
	cv::waitKey(0);
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return -1;
	ResizeExample(srcImage);
	return 0;
}
