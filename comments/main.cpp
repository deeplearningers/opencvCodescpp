// ���ܣ����� 5-23 ����������
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace cv;
using namespace std;
// ����ͼ���
void cacMoments(cv::Mat src)
{
	Mat srcGray;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// ��˹�˲�
	GaussianBlur(src, src, Size(3, 3), 0.1, 0, BORDER_DEFAULT);
	// �Ҷ�ת��
	cvtColor(src, srcGray, CV_RGB2GRAY);
	// �����߽���
	findContours(srcGray, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	// ���Ʊ߽�
	// drawContours(src, contours, -1, cvScalar(0,0,255));
	printf("Number of contours: %d\n", (int)contours.size());
	// ����������
	vector<Moments> mu(contours.size());
	for (int i = 0; i < (int)contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}
	// �����ؼ���ͼ���������
	for (int i = 0; i < (int)contours.size(); i++)
	{
		// ��� ���� �߽���������
		int area = mu[i].m00;
		int cx = mu[i].m10 / mu[i].m00;
		int cy = mu[i].m01 / mu[i].m00;
		int perimeter = arcLength(contours.at(i), true);
		// ��Բ
		if (int(contours.at(i).size()) <= 5)
		{
			continue;
		}
		else
		{
			RotatedRect rRect = fitEllipse(contours.at(i));
			double orientation = rRect.angle;
			double orientation_rads = orientation*3.1416 / 180;
			double majorAxis = rRect.size.height > rRect.size.width ? rRect.size.height : rRect.size.width;
			double minorAxis = rRect.size.height > rRect.size.width ? rRect.size.width : rRect.size.height;
			// Բ�ζ� ������ �ܳ� ֱ��
			double roundness = pow(perimeter, 2) / (2 * 3.1416*area);
			double eccentricity = sqrt(1 - pow(minorAxis / majorAxis, 2));
			double ratio = (minorAxis / majorAxis) * 100;
			double diameter = sqrt((4 * area) / 3.1416);
			// ������������Ϣ
			printf("Area: %d\n", area);
			printf("Perimeter: %d\n", perimeter);
			printf("Major Axis: %.1f\n", majorAxis);
			printf("Minor Axis: %.1f\n", minorAxis);
			printf("Orientation: %.1f\n", orientation);
			printf("Roundness: %.1f\n", roundness);
			printf("Eccentricity: %.1f\n", eccentricity);
			printf("Ratio: %.1f\n", ratio);
			printf("Diameter: %.1f\n", diameter);
			printf("\n");
			// ���ƾ��μ���Բ
			ellipse(src, rRect, cvScalar(0, 255, 0));
			rectangle(src, boundingRect(contours.at(i)), cvScalar(0, 0, 255));
			// �����������
			//line(src, Point(cx-30, cy), Point(cx+30, cy), cvScalar(0,0,255));
			//line(src, Point(cx, cy-30), Point(cx, cy+30), cvScalar(0,0,255));
			// ������ʼ��
			line(src, Point(cx, cy), Point((int)(cx + 30 * cos(orientation_rads)),
				(int)(cy + 30 * sin(orientation_rads))), cvScalar(255, 0, 0), 1);
			// ���ͼ����ʼ
			char pChar[100];
			sprintf(pChar, "Ori: %.0f", orientation);
			putText(src, pChar, Point(cx, cy), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255));
		}
	}
	cv::imshow("result", src);
}
int main(){
	cv::Mat srcImage = imread("..\\images\\img07.JPG");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	// ����������
	cacMoments(srcImage);
	cv::waitKey(0);
	return(0);
}