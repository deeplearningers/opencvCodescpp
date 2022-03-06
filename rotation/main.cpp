// ���ܣ����� 2-11 ��ת�任
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;
cv::Mat angelRotate(cv::Mat& src, int angle)
{
	// �Ƕ�ת������
	float alpha = angle * CV_PI / 180;
	// ������ת����
	float rotateMat[3][3] = {
		{ cos(alpha), -sin(alpha), 0 },
		{ sin(alpha), cos(alpha), 0 },
		{ 0, 0, 1 } };
	int nSrcRows = src.rows;
	int nSrcCols = src.cols;
	// ������ת��ͼ������������λ��
	float a1 = nSrcCols * rotateMat[0][0];
	float b1 = nSrcCols * rotateMat[1][0];
	float a2 = nSrcCols * rotateMat[0][0] +
		nSrcRows * rotateMat[0][1];
	float b2 = nSrcCols * rotateMat[1][0] +
		nSrcRows * rotateMat[1][1];
	float a3 = nSrcRows * rotateMat[0][1];
	float b3 = nSrcRows * rotateMat[1][1];
	// �������ֵ��
	float kxMin = min(min(min(0.0f, a1), a2), a3);
	float kxMax = max(max(max(0.0f, a1), a2), a3);
	float kyMin = min(min(min(0.0f, b1), b2), b3);
	float kyMax = max(max(max(0.0f, b1), b2), b3);
	// �����������ĳߴ�
	int nRows = abs(kxMax - kxMin);
	int nCols = abs(kyMax - kyMin);
	cv::Mat dst(nRows, nCols, src.type(), cv::Scalar::all(0));
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			// ��ת����ת��
			int x = (j + kxMin) * rotateMat[0][0] -
				(i + kyMin) * rotateMat[0][1];
			int y = -(j + kxMin) * rotateMat[1][0] +
				(i + kyMin) * rotateMat[1][1];
			if ((x >= 0) && (x < nSrcCols) &&
				(y >= 0) && (y < nSrcRows))
			{
				dst.at<cv::Vec3b>(i, j) =
					src.at<cv::Vec3b>(y, x);
			}
		}
	}
	return dst;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\pool.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	int angle = 30;
	cv::Mat resultImage = angelRotate(srcImage, angle);
	imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
