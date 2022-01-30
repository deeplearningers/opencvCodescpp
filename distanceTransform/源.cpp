// ���ܣ����� 3-19 distanceTransform ����任
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return -1;
	// ת��Ϊ�Ҷ�ͼ��
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	// ת��Ϊ��ֵͼ��
	cv::Mat srcBinary;
	threshold(srcGray, srcBinary, 160, 255, cv::THRESH_BINARY);
	// ����任
	cv::Mat dstImage;
	cv::distanceTransform(srcBinary, dstImage, CV_DIST_C,
		CV_DIST_MASK_PRECISE);
	// ��һ������
	cv::normalize(dstImage, dstImage, 0, 1., cv::NORM_MINMAX);
	cv::imshow("srcBinary", srcBinary);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
