// ���ܣ����� 8-3 SIFT ������⼰ƥ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
// ע�⣺�����±���OpenCV3.1 contrib�������鸽¼2
#include <opencv2/highgui//highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// ����ͼ���SIFT������ƥ��
cv::Mat cacSIFTFeatureAndCompare(cv::Mat srcImage1,
	cv::Mat srcImage2)
{
	CV_Assert(srcImage1.data != NULL && srcImage2.data != NULL);
	// ת��Ϊ�Ҷ�
	cv::Mat grayMat1, grayMat2;
	cv::cvtColor(srcImage1, grayMat1, CV_RGB2GRAY);
	cv::cvtColor(srcImage2, grayMat2, CV_RGB2GRAY);
	//��һ��
	cv::normalize(grayMat1, grayMat1, 0, 255, cv::NORM_MINMAX);
	cv::normalize(grayMat2, grayMat2, 0, 255, cv::NORM_MINMAX);
	// ��ʼ��SIFT���������
	cv::SiftFeatureDetector detector;
	cv::SiftDescriptorExtractor extractor;
	// �ؼ��㼰����������������
	vector<cv::KeyPoint> keyPoints1, keyPoints2;
	cv::Mat descriptorMat1, descriptorMat2;
	//��������
	detector.detect(grayMat1, keyPoints1);
	detector.detect(grayMat2, keyPoints2);
	//���������������
	extractor.compute(grayMat1, keyPoints1, descriptorMat1);
	extractor.compute(grayMat2, keyPoints2, descriptorMat2);

		// ��������ƥ���
		cv::BruteForceMatcher<cv::L2<float>> matcher;
		vector< cv::DMatch > matches;
		matcher.match(descriptorMat1, descriptorMat2, matches);
		//��������
		int N = 80;
		nth_element(matches.begin(), matches.begin() + N - 1, matches.end());
		//ȥ�������㲻ƥ�����
		matches.erase(matches.begin() + N, matches.end());
		//���Ƽ����
		cv::Mat matchMat;
		cv::drawMatches(srcImage1, keyPoints1, srcImage2, keyPoints2, matches, matchMat);
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
	cv::Mat siftMat = cacSIFTFeatureAndCompare(srcImage1, srcImage2);
	cv::imshow("matchMat", siftMat);
	cv::waitKey(0);
	return 0;
}