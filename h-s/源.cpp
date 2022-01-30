// ���ܣ����� 3-7 2 ά H-S ֱ��ͼ��ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream> 
using namespace std;
using namespace cv;
int main()
{
	cv::Mat srcImage, hsvMat;
	srcImage = cv::imread("..\\images\\flower3.jpg");
	if (srcImage.empty())
		return -1;
	cv::cvtColor(srcImage, hsvMat, CV_BGR2HSV);
	// ��ʼ���ҶȽײ���
	int hbins = 30, sbins = 32;
	int histSize[] = { hbins, sbins };
	// �Ҷȱ仯��Χ����
	float hranges[] = { 0, 180 };
	// ���Ͷȱ仯��Χ
	float sranges[] = { 0, 256 };
	const float* ranges[] = { hranges, sranges };
	cv::MatND hist;
	// ѡȡ����ֱ��ͼͨ��
	int channels[] = { 0, 1 };
	// ���㵱ǰͨ��ֱ��ͼ
	cv::calcHist(&hsvMat, 1, channels, cv::Mat(),
		hist, 2, histSize, ranges,
		true, false);
	double maxVal = 0;
	// �ҵ�ֱ��ͼ�����ֵ
	cv::minMaxLoc(hist, 0, &maxVal, 0, 0);
	int scale = 10;
	cv::Mat histImg = cv::Mat::zeros(sbins*scale, hbins * scale,CV_8UC3);
	// ����hsͨ��
	for (int h = 0; h < hbins; h++)//��
	{
		for (int s = 0; s < sbins; s++)//��
		{
			float binVal = hist.at<float>(h,s);
			// �������ֵ����任��Χ
			int intensity = cvRound(binVal * 255 / maxVal);
			// ��ͼ��ʾ
			cv::rectangle(histImg,
				cv::Point(h*scale, s*scale),
				cv::Point((h + 1)*scale - 1,
				(s + 1)*scale - 1),
				cv::Scalar::all(intensity),
				CV_FILLED);
		}
	}
	cv::imshow("Source", srcImage);
	cv::imshow("H-S Histogram", histImg);
	cv::waitKey();
}
