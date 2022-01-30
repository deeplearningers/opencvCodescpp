// ���ܣ����� 6-1 ��ʴ���Ͳ���
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
	cv::Mat srcImage = cv::imread("..\\images\\test.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::Mat segDst, dilDst, eroDst;
	// ��ͨ����ֵ��
	cv::inRange(srcGray, cv::Scalar(0, 0, 100),
		cv::Scalar(40, 30, 255), segDst);
	// ����ṹԪ��
	cv::Mat element = cv::getStructuringElement(
		cv::MORPH_ELLIPSE, cv::Size(5, 5));
	// ��ʴ���Ͳ���
	cv::dilate(segDst, dilDst, element);
	cv::erode(segDst, eroDst, element,cv::Point(-1,-1),1,0);
	cv::imshow(" srcGray ", srcGray);
	cv::imshow(" segDst ", segDst);
	cv::imshow(" dilDst ", dilDst);
	cv::imshow(" eroDst ", eroDst);
	cv::waitKey();
	return 0;
}