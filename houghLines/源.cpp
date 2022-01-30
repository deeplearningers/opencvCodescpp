// ���ܣ����� 5-16 ����任�߼��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcImage =
		cv::imread("..\\images\\building.jpg", 0);
	if (!srcImage.data)
		return -1;
	cv::Mat edgeMat, houghMat;
	GaussianBlur(srcImage, srcImage, cv::Size(5, 5), 0.5, 0.5, 4);
	// Canny��Ե��� ��ֵͼ��
	Canny(srcImage, edgeMat,70,250, 3);
	cvtColor(edgeMat, houghMat, CV_GRAY2BGR);
#if 0
	// ��׼�Ļ���任
	vector<Vec2f> lines;
	HoughLines(edgeMat, lines, 1, CV_PI / 180, 100, 0, 0);
	for (size_t i = 0; i < lines.size(); i++)
	{
		// ����ֱ�߲������ʽ������Ӧ�����
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(houghMat, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
#else
	// ͳ�Ƹ��ʵĻ���任
	vector<Vec4i> lines;
	HoughLinesP(edgeMat, lines, 1, CV_PI / 180,35,60,200);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		// �����߼����
		line(houghMat, Point(l[0], l[1]),
			Point(l[2], l[3]), Scalar(0, 0, 255), 1, CV_AA);
	}
#endif
	cv::imshow("srcImage", srcImage);
	cv::imshow("houghMat", houghMat);
	cv::waitKey();
	return 0;
}
