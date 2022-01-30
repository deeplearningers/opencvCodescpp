// ���ܣ����� 3-4 ˫��ֵ����ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
int main()
{
	// ͼ���ȡ���ж�
	cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
	if (!srcImage.data)
		return 1;
	// �Ҷ�ת��
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::imshow("srcGray", srcGray);
	// ��ʼ����ֵ����
	const int maxVal = 255;
	int low_threshold = 120;
	int high_threshold = 180;
	cv::Mat dstTempImage1, dstTempImage2, dstImage;
	// С��ֵ��Դ�Ҷ�ͼ�������ֵ������
	cv::threshold(srcGray, dstTempImage1,
		low_threshold, maxVal, cv::THRESH_BINARY);
	// ����ֵ��Դ�Ҷ�ͼ�������ֵ������
	cv::threshold(srcGray, dstTempImage2,
		high_threshold, maxVal, cv::THRESH_BINARY_INV);
	// ����������õ���ֵ�����
	cv::bitwise_and(dstTempImage1,
		dstTempImage2, dstImage);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
