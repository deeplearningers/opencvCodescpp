// ���ܣ����� 8-5 ORB ���������ƥ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>

using namespace cv;
// ����ͼ���ORB������ƥ��
cv::Mat cacORBFeatureAndCompare(cv::Mat srcImage1,
	cv::Mat srcImage2)
{
	CV_Assert(srcImage1.data != NULL && srcImage2.data != NULL);
	// ת��Ϊ�Ҷ�
	cv::Mat grayMat1, grayMat2;
	cv::cvtColor(srcImage1, grayMat1, CV_RGB2GRAY);
	cv::cvtColor(srcImage2, grayMat2, CV_RGB2GRAY);
	// �ؼ�����
	std::vector<KeyPoint> keyPoints1, keyPoints2;

	Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);//��ΪĬ�ϲ���

	orb->detect(srcImage1, keyPoints1);
	orb->detect(srcImage2, keyPoints2);
	// ������������
	cv::Mat descriptorMat1, descriptorMat2;
	orb->compute(srcImage1, keyPoints1, descriptorMat1);
	orb->compute(srcImage2, keyPoints2, descriptorMat2);

	// ����ƥ��
	BFMatcher matcher(NORM_HAMMING);
	std::vector<DMatch> mathces;
	matcher.match(descriptorMat1, descriptorMat2, mathces);
	// ����ƥ��㼯
	Mat matchMat;
	drawMatches(srcImage1, keyPoints1,
		srcImage2, keyPoints2, mathces, matchMat);
	//cv::imshow("Mathces", matchMat);
	return matchMat;
}
int main()
{
	// ��ȡԴͼ�񼰴�ƥ��ͼ��
	cv::Mat srcImage1 =
		cv::imread("..\\images\\hand1.jpg", 1);
	if (srcImage1.empty())
		return -1;
	cv::Mat srcImage2 =
		cv::imread("..\\images\\hand3.jpg", 1);
	if (srcImage2.empty())
		return -1;
	cv::Mat  matchMat = cacORBFeatureAndCompare(srcImage1, srcImage2);
	cv::imshow("matchMat", matchMat);
	cv::waitKey(0);
	return 0;
}
