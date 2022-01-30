// ���ܣ�����1-7  ����Sublimeʾ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
int main()
{
	// ��ȡͼ��
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	// ͼ���ȡ�Ƿ�ɹ�
	if (!srcImage.data)
		return 1;
	// ��ͼ�����������ת,��ת����  
	cv::Point2f center =
		cv::Point2f(srcImage.cols / 2, srcImage.rows / 2);
	// ��ת�Ƕ� 
	double angle = 60;
	// ���ų߶� 
	double scale = 0.5;
	// ������ת�ķ���任����
	cv::Mat rotateImage;
	rotateImage = cv::getRotationMatrix2D(center,
		angle, scale);
	// ����任 
	cv::Mat rotateImg;
	cv::warpAffine(srcImage, rotateImg, rotateImage,
		srcImage.size());
	// ͼ����ʾ 
	cv::imshow("srcImage", srcImage);
	cv::imshow("rotateImg", rotateImg);
	cv::waitKey(0);
	return 0;
}
