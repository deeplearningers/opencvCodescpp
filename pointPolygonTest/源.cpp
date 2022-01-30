// ���ܣ����� 5-24 �����β���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
vector<vector<Point> > closed_contours;
vector<Vec4i> heirarchy;
cv::Mat contoursAllMat;
// ��������ν���
vector<vector<Point> > cacContoursClosed(
	vector<vector<Point> > contours)
{
	vector<vector<Point> > vContours;
	vContours.resize(contours.size());
	for (int i = 0; i < contours.size(); i++)
		approxPolyDP(contours[i], vContours[i], 0.1, true);
	return vContours;
}
// ��С�㼯�߽�����
int cacContoursSmall(Point p, vector<vector<Point> > contours,
	vector<Vec4i> heirarchy)
{
	int idx = 0, prev_idx = -1;
	while (idx >= 0)
	{
		vector<Point> c = contours[idx];
		// �����β���
		double d = pointPolygonTest(c, p, false);
		// �жϵ㼯�Ƿ��ڶ������
		if (d > 0)
		{
			prev_idx = idx;
			idx = heirarchy[idx][2];
		}
		// �����ڣ�������������һ��
		else
			idx = heirarchy[idx][0];
	}
	return prev_idx;
}
// �����������Ӧ
void on_mouse(int event, int x, int y, int, void *)
{
	// �¼����ȷ��
	if (event != EVENT_LBUTTONDOWN)
		return;
	Point p(x, y);
	// Ѱ����С����������
	int idxContour = cacContoursSmall(p, closed_contours,
		heirarchy);
	// �����������������ʾ������
	if (idxContour < 0)
	{
		imshow("Contours", contoursAllMat);
		return;
	}
	// ��ͼ������С���������
	vector<vector<Point> > viewContour;
	viewContour.push_back(closed_contours[idxContour]);
	if (!viewContour.empty())
	{
		Mat result = contoursAllMat.clone();
		// ������������
		drawContours(result, viewContour, -1,
			Scalar(0, 0, 0), 4);
		imshow("Contours", result);
	}
}
int main()
{
	cv::Mat srcImage = imread("..\\images\\circle.jpg");
	if (!srcImage.data)
		return -1;
cv:imshow("srcImage", srcImage);
	contoursAllMat = srcImage.clone();
	cv::Mat srcGray, edges;
	// ��Ե���
	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	Canny(srcGray, edges, 50, 100);
	// Ѱ���������
	vector<vector<Point> > contours;
	findContours(edges, contours, heirarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	// ȷ�ϼ��������ķ����
	closed_contours = cacContoursClosed(contours);
	// ������������
	drawContours(srcImage, closed_contours, -1,
		Scalar(0, 255, 0),2);
	imshow("Contours", srcImage);
	// ���ص��¼�
	setMouseCallback("Contours", on_mouse);
	while (char(waitKey(1)) != 'q') {}
	return 0;
}
