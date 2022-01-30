// ���ܣ����� 5-26 Harris �ǵ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;
void CornerHarris(const Mat& srcImage, Mat& result,
	int blockSize, int kSize, double k)
{
	Mat src;
	srcImage.copyTo(src);
	result.create(src.size(), CV_32F);
	int depth = src.depth();
	// �����Ĥ�ߴ�
	double scale = (double)(1 << ((kSize > 0 ?
	kSize : 3) - 1)) * blockSize;
	if (depth == CV_8U)
		scale *= 255.;
	scale = 1. / scale;
	// sobel�˲�
	Mat dx, dy;
	Sobel(src, dx, CV_32F, 1, 0, kSize, scale, 0);
	Sobel(src, dy, CV_32F, 0, 1, kSize, scale, 0);
	Size size = src.size();
	cv::Mat cov(size, CV_32FC3);
	int i, j;
	// ���ˮƽ����ֱ�ݶ�
	for (i = 0; i < size.height; i++){
		float *covData = (float*)(cov.data + i*cov.step);
		const float *dxData = (const float*)(dx.data + i*dx.step);
		const float *dyData = (const float*)(dy.data + i*dy.step);
		for (j = 0; j < size.width; j++)
		{
			float dx_ = dxData[j];
			float dy_ = dyData[j];
			covData[3 * j] = dx_*dx_;
			covData[3 * j + 1] = dx_*dy_;
			covData[3 * j + 2] = dy_*dy_;
		}
	}
	// ���㴰�������
	boxFilter(cov, cov, cov.depth(),
		Size(blockSize, blockSize), Point(-1, -1), false);
	// �ж�ͼ��������
	if (cov.isContinuous() && result.isContinuous())
	{
		size.width *= size.height;
		size.height = 1;
	}
	else
		size = result.size();
	// ������Ӧ���� 
	for (i = 0; i < size.height; i++)
	{
		// ��ȡͼ�����ָ��
		float *resultData = (float*)(result.data + i*result.step);
		const float *covData = (const float*)(cov.data + i*cov.step);
		for (j = 0; j < size.width; j++)
		{
			// ������Ӧ����
			float a = covData[3 * j];
			float b = covData[3 * j + 1];
			float c = covData[3 * j + 2];
			resultData[j] = a*c - b*b - k*(a + c)*(a + c);
		}
	}
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower2.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat srcGray, result;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	result = Mat::zeros(srcImage.size(), CV_32FC1);
	// �ǵ������
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	// �ǵ���
	// cornerHarris( srcGray, result, blockSize, apertureSize, k, BORDER_DEFAULT );
	CornerHarris(srcGray, result, blockSize, apertureSize, k);
	// �����һ��
	normalize(result, result, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(result, result);
	// ��ͼ�ǵ�����
	for (int j = 0; j < result.rows; j++)
	{
		for (int i = 0; i < result.cols; i++)
		{
			if ((int)(result.at<uchar>(j, i)) > 150)
			{
				circle(srcImage, Point(i, j), 5, Scalar(0), 1, 8, 0);
			}
		}
	}
	cv::imshow("result", srcImage);
	cv::waitKey(0);
	return 0;
}
