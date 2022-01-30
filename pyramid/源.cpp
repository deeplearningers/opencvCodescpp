// ���ܣ����� 4-4 ͼ�����������
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
// ͼ���������������
void Pyramid(cv::Mat srcImage)
{
	// ����ͼ��Դ�ߴ��ж��Ƿ���Ҫ����
	if (srcImage.rows > 400 && srcImage.cols > 400)
		cv::resize(srcImage, srcImage, cv::Size(), 0.5, 0.5);
	else
		cv::resize(srcImage, srcImage, cv::Size(), 1, 1);
	cv::imshow("srcImage", srcImage);
	cv::Mat pyrDownImage, pyrUpImage;
	// �²�������
	pyrDown(srcImage, pyrDownImage,
		cv::Size(srcImage.cols / 2, srcImage.rows / 2));
	cv::imshow("pyrDown", pyrDownImage);
	// �ϲ�������
	pyrUp(srcImage, pyrUpImage,
		cv::Size(srcImage.cols * 2, srcImage.rows * 2));
	cv::imshow("pyrUp", pyrUpImage);
	// ���²��������ع�
	cv::Mat pyrBuildImage;
	pyrUp(pyrDownImage, pyrBuildImage,
		cv::Size(pyrDownImage.cols * 2, pyrDownImage.rows * 2));
	cv::imshow("pyrBuildImage", pyrBuildImage);
	// �Ƚ��ع�����
	cv::Mat diffImage;
	cv::absdiff(srcImage, pyrBuildImage, diffImage);
	cv::imshow("diffImage", diffImage);
	cv::waitKey(0);
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return -1;
	Pyramid(srcImage);
	return 0;
}
