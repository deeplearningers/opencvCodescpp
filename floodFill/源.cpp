// ���ܣ����� 7-3 FloodFill ͼ��ָ�
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
// ��ʶ������
Mat image, gray, mask;
int ffillMode = 1;
int loDiff = 20, upDiff = 20;
int connectivity = 4;
int isColor = true;
bool useMask = false;
int newMaskVal = 255;
// �����Ӧ����
static void onMouse(int event, int x, int y, int, void*)
{
	if (event != CV_EVENT_LBUTTONDOWN)
		return;
	// floodfill��������
	Point seed = Point(x, y);
	int lo = ffillMode == 0 ? 0 : loDiff;
	int up = ffillMode == 0 ? 0 : upDiff;
	int flags = connectivity + (newMaskVal << 8) +
		(ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
	// ��ɫ�������ѡȡ
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;
	// ��ɫѡ��
	Scalar newVal = isColor ? Scalar(b, g, r)
		: Scalar(r*0.299 + g*0.587 + b*0.114);
	Mat dst = isColor ? image : gray;
	int area;
	// ���ݱ�־λѡ�񷺺����
	if (useMask)
	{
		// ��ֵ������
		threshold(mask, mask, 1, 128, CV_THRESH_BINARY);
		area = floodFill(dst, mask, seed,
			newVal, &ccomp, Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
		imshow("mask", mask);
	}
	else
	{
		// �������
		area = floodFill(dst, seed, newVal, &ccomp,
			Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
	}
	imshow("image", dst);
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (srcImage.empty())
		return 0;
	srcImage.copyTo(image);
	cvtColor(srcImage, gray, CV_BGR2GRAY);
	mask.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);
	// �����Ӧ�ص�����
	namedWindow("image", 0);
	setMouseCallback("image", onMouse, 0);
	for (;;)
	{
		imshow("image", isColor ? image : gray);
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "Exiting ...\n";
			break;
		}
		if (c == 'r')
		{
			cout << "Original image is restored\n";
			srcImage.copyTo(image);
			cvtColor(image, gray, CV_BGR2GRAY);
			mask = Scalar::all(0);
		}
	}
	return 0;
}
