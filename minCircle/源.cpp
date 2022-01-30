// ���ܣ����� 5-21 ��С������Բ����
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
	cv::Mat img(500, 500, CV_8UC3);
	// �����������
	RNG& rng = theRNG();
	for (;;)
	{
		int i, count = rng.uniform(1, 101);
		vector<Point> points;
		// ������ɶ�ά�㼯
		for (i = 0; i < count; i++)
		{
			Point pt;
			pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
			pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
			points.push_back(pt);
		}
		// ��ά�㼯��������һ����б��С����ľ���
		RotatedRect box = minAreaRect(Mat(points));
		Point2f center, vtx[4];
		float radius = 0;
		// ��������ȫ��Χ����������СԲ
		minEnclosingCircle(Mat(points), center, radius);
		box.points(vtx);
		img = Scalar::all(0);
		// ��ͼԲ��ʾ
		for (i = 0; i < count; i++)
			circle(img, points[i], 3, Scalar(0, 0, 255), CV_FILLED, CV_AA);
		// ��ͼ����ʾ
		for (i = 0; i < 4; i++)
			line(img, vtx[i], vtx[(i + 1) % 4], Scalar(0, 255, 0), 1, CV_AA);
		circle(img, center, cvRound(radius), Scalar(0, 255, 255), 1, CV_AA);
		imshow("rect & circle", img);
		char key = (char)cvWaitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}
	return 0;
}
