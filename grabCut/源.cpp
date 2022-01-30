// ���ܣ����� 7-5 Grabcut ͼ��ָ�
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace cv;
using namespace std;
// ȫ�ֱ�������
cv::Point point1, point2;
int drag = 0;
cv::Rect rect;
cv::Mat srcImage, roiImg;
bool select_flag = true;
cv::Mat rectimg;
vector<Point>Pf, Pb;
// �����Ӧ�ص�
void mouseHandler(int event, int x, int y, int flags, void* param)
{
	// ������� 
	if (event == CV_EVENT_LBUTTONDOWN && !drag)
	{
		point1 = Point(x, y);
		drag = 1;
	}
	// ����ƶ�
	else if (event == CV_EVENT_MOUSEMOVE && drag)
	{
		Mat img1 = srcImage.clone();
		point2 = Point(x, y);
		rectangle(img1, point1, point2,
			CV_RGB(255, 0, 0), 3, 8, 0);
		imshow("srcImage", img1);
	}
	// ���̧������ק��־
	else if (event == CV_EVENT_LBUTTONUP && drag)
	{
		point2 = Point(x, y);
		rect = Rect(point1.x, point1.y, x - point1.x, y - point1.y);
		drag = 0;
		roiImg = srcImage(rect);
	}
	// �Ҽ�����
	else if (event == CV_EVENT_RBUTTONDOWN)
	{
		select_flag = true;
		drag = 0;
		imshow("ROI", roiImg);
	}
}
int main()
{
	srcImage = imread("..\\images\\sea.jpg");
	if (srcImage.empty())
		return -1;
	// ����ǰ�������ͼ��
	cv::Mat srcImage2 = srcImage.clone();
	cv::Mat foreground(srcImage.size(),
		CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat result(srcImage.size(), CV_8UC1);
	// grabcut�ָ�ǰ���뱳��
	cv::Mat fgMat, bgMat;
	namedWindow("srcImage", 1);
	imshow("srcImage", srcImage);
	// ��������
	int i =10;
	std::cout <<i<<" "<<"iters" << std::endl;
	// �����Ӧ
	setMouseCallback("srcImage", mouseHandler, NULL);
	// ѡ��������Ч������esc�˳�
	while ((select_flag == true) && (waitKey(0) != 27))
	{
		// ͼ���㷨��Ϥ
		grabCut(srcImage, result, rect, bgMat,
			fgMat, 1, GC_INIT_WITH_RECT);
		 //ͼ��ƥ��
		cv::compare(result, cv::GC_PR_FGD,
			result, cv::CMP_EQ);
		 //����ǰ��ͼ��
		srcImage.copyTo(foreground, result);
		imshow("foreground", foreground);
	}
	cv::waitKey(0);
	return 0;
}