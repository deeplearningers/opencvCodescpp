// ���ܣ����� 3-3 adaptiveThreshold ��ֵ����ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��//
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
	cv::Mat dstImage;
	// ��ʼ������Ӧ��ֵ����
	int blockSize = 5;
	int constValue = 10;
	const int maxVal = 255;
	/* ����Ӧ��ֵ�㷨
	0��ADAPTIVE_THRESH_MEAN_C
	1: ADAPTIVE_THRESH_GAUSSIAN_C
	��ֵ����
	0: THRESH_BINARY
	1: THRESH_BINARY_INV */

	int adaptiveMethod =0;
	int thresholdType = 0;
	// ͼ������Ӧ��ֵ����
	cv::adaptiveThreshold(srcGray, dstImage,
		maxVal, adaptiveMethod,
		thresholdType, blockSize,
		constValue);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
