// ���ܣ����� 2-19 ���� createTrackbar ���ж�ֵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
//createTrackbar�Ļص���Ӧ����
void onChangeTrackBar(int pos, void* data)
{
	// ǿ������ת��
	cv::Mat srcImage = *(cv::Mat*)(data);
	cv::Mat dstImage;
	// ���ݻ�������ֵ���ж�ֵ��
	cv::threshold(srcImage, dstImage, pos, 255, 0);
	cv::imshow("dyn_threshold", dstImage);
}
int main()
{
	// Դͼ�����뼰�ж�
	cv::Mat srcImage = cv::imread("..\\images\\flower4.jpg");
	if (!srcImage.data)
		return 1;
	// ת��Ϊ�Ҷ�ͼ��
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::namedWindow("dyn_threshold");
	cv::imshow("dyn_threshold", srcGray);
	//����������createTrackbar�����ûص�����
	createTrackbar("pos", "dyn_threshold",
		0, 255, onChangeTrackBar, &srcGray);
	cv::waitKey(0);
	return 0;
}
