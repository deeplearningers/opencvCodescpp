// ���ܣ�5-6 OpenCV �Դ���ͼ���Ե����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
int main()
{
	cv::Mat srcImage = imread("..\\images\\building.jpg");
	if (!srcImage.data)
		return -1;
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	imshow("srcGray", srcGray);
	// �����Եͼ��ˮƽ����ֱ
	cv::Mat edgeMat, edgeXMat, edgeYMat;
	// ��x����Sobel��Ե
	Sobel(srcGray, edgeXMat, CV_16S, 1, 0, 3, 1,
		0, BORDER_DEFAULT);
	// ��y����Sobel��Ե
	Sobel(srcGray, edgeYMat, CV_16S, 0, 1, 3, 1,
		0, BORDER_DEFAULT);
	// ���Ա任ת����������Ԫ�س�8λ�޷�������
	convertScaleAbs(edgeXMat, edgeXMat);
	convertScaleAbs(edgeYMat, edgeYMat);
	// x��y�����Ե����
	addWeighted(edgeXMat, 0.5, edgeYMat, 0.5, 0, edgeMat);
	cv::imshow("edgeYMat", edgeYMat);
	imshow("edgeMat", edgeMat);
	// ����Scharr��Եͼ��
	cv::Mat edgeMatS, edgeXMatS, edgeYMatS;
	// ����x����Scharr��Ե
	Scharr(srcGray, edgeXMatS, CV_16S, 1, 0, 1,
		0, BORDER_DEFAULT);
	convertScaleAbs(edgeXMatS, edgeXMatS);
	// ����y����Scharr��Ե
	Scharr(srcGray, edgeYMatS, CV_16S, 0, 1, 1,
		0, BORDER_DEFAULT);
	// ���Ա任ת����������Ԫ�س�8λ�޷�������
	convertScaleAbs(edgeYMatS, edgeYMatS);
	// x��y�����Ե����
	addWeighted(edgeXMatS, 0.5, edgeYMatS, 0.5, 0, edgeMatS);
	cv::imshow("edgeMatS", edgeMatS);
	cv::waitKey(0);
	return 0;
}
