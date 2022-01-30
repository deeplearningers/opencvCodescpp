// ���ܣ����� 3-16 ֱ��ͼ����ͶӰ
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	// ����Դͼ����֤
	cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
	if (!srcImage.data)
		return 1;
	// ת���� HSV �ռ�
	cv::Mat hsvImage;
	cvtColor(srcImage, hsvImage, CV_BGR2HSV);
	// Hue ͨ������ 
	cv::Mat hueImage;
	hueImage.create(hsvImage.size(), hsvImage.depth());
	int ch[] = { 0, 0 };
	mixChannels(&hsvImage, 1, &hueImage, 1, ch, 1);
	// ��ʼ��ֱ��ͼ�������
	int bins = 25;//����
	cv::MatND hist;
	int histSize = MAX(bins, 2);
	float hue_range[] = { 0, 100 };
	const float* ranges = { hue_range };
	// ����ֱ��ͼ
	calcHist(&hueImage, 1, 0, cv::Mat(),
		hist, 1, &histSize, &ranges, true, false);
	// ��һ��ֱ��ͼ
	normalize(hist, hist, 0, 255, cv::NORM_MINMAX,
		-1, cv::Mat());
	// ���㷴��ͶӰ
	MatND backproj;
	calcBackProject(&hueImage, 1, 0, hist, backproj,
		&ranges, 1, true);
	// �������ͼ��
	int w = 320; int h = 360;
	int bin_w = cvRound((double)w / histSize);
	cv::Mat histImg = cv::Mat::zeros(w, h, CV_8UC3);
	for (int i = 0; i < bins; i++)
	{
		// ����ֱ��ͼ
		rectangle(histImg, cv::Point(i * bin_w, h),
			cv::Point((i + 1)*bin_w,
			h - cvRound(hist.at<float>(i) * h / 255.0)),
			cv::Scalar(0, 0, 255), -1);
	}
	// ��ʾԴͼ���뷴��ͶӰͼ��
	imshow("BackProj", backproj);
	imshow("srcImage", srcImage);
	imshow("Histogram", histImg);
	// ֱ��ͼ���⻯
	cv::equalizeHist(backproj, backproj);
	imshow("backproj_equa", backproj);
	waitKey(0);
	return 0;
}
