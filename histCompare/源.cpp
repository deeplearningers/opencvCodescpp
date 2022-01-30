// ���ܣ����� 3-15 ֱ��ͼ�Ա�ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
// ***Opencv tutorials***//
int main(int argc, char** argv)
{
	cv::Mat src_base, hsv_base;
	cv::Mat src_test1, hsv_test1;
	cv::Mat src_test2, hsv_test2;
	cv::Mat hsv_half_down;
	// ���ز�ͬ����������ͼ��
	src_base = cv::imread("..\\images\\hand1.jpg");
	src_test1 = cv::imread("..\\images\\hand2.jpg");
	src_test2 = cv::imread("..\\images\\hand3.jpg");
	cv::imshow("HistComSource0", src_base);
	cv::imshow("HistComSource1", src_test1);
	cv::imshow("HistComSource2", src_test2);
	cv::waitKey(0);
	if (!src_base.data || !src_test1.data || !src_test2.data)
		return 1;
	// �ֱ�ת��ΪHSVͨ���µ�ͼ��
	cvtColor(src_base, hsv_base, CV_BGR2HSV);
	cvtColor(src_test1, hsv_test1, CV_BGR2HSV);
	cvtColor(src_test2, hsv_test2, CV_BGR2HSV);
	hsv_half_down = hsv_base(cv::Range(hsv_base.rows / 2,
		hsv_base.rows - 1), cv::Range(0,
		hsv_base.cols - 1));
	/// hueͨ������Ϊ30bins, saturatoinͨ������32bins
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };
	// ����hue��ȡֵ��0��256, saturationȡֵ��0��180
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	int channels[] = { 0, 1 };
	// ����ֱ��ͼ
	cv::MatND hist_base;
	cv::MatND hist_half_down;
	cv::MatND hist_test1;
	cv::MatND hist_test2;
	// ������Ӧͨ������ֱ��ͼ
	cv::calcHist(&hsv_base, 1, channels, cv::Mat(),
		hist_base, 2, histSize, ranges, true, false);
	cv::normalize(hist_base, hist_base, 0, 1,
		cv::NORM_MINMAX, -1, cv::Mat());

	cv::calcHist(&hsv_half_down, 1, channels, cv::Mat(),
		hist_half_down, 2, histSize, ranges, true, false);
	cv::normalize(hist_half_down, hist_half_down, 0, 1,
		cv::NORM_MINMAX, -1, cv::Mat());

	cv::calcHist(&hsv_test1, 1, channels, cv::Mat(),
		hist_test1, 2, histSize, ranges, true, false);
	cv::normalize(hist_test1, hist_test1, 0, 1,
		cv::NORM_MINMAX, -1, cv::Mat());

	cv::calcHist(&hsv_test2, 1, channels, cv::Mat(),
		hist_test2, 2, histSize, ranges, true, false);
	cv::normalize(hist_test2, hist_test2, 0, 1,
		cv::NORM_MINMAX, -1, cv::Mat());
	// Ӧ�ò�ֱͬ��ͼ�Աȷ���
	for (int i = 0; i < 4; i++)
	{
		int compare_method = i;
		double base_base = compareHist(hist_base,
			hist_base, compare_method);
		double base_half = compareHist(hist_base,
			hist_half_down, compare_method);
		double base_test1 = compareHist(hist_base,
			hist_test1, compare_method);
		double base_test2 = compareHist(hist_base,
			hist_test2, compare_method);
		printf(" Method [%d] Base_Base, Base-Half,Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n",
			i, base_base, base_half, base_test1, base_test2);
	}
	return 0;
}
