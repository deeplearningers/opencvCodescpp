// ���ܣ����� 4-9 ͼ����Ӹ�˹����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
using namespace cv;
using namespace std;
double generateGaussianNoise(double mu, double sigma)
{
	// ����Сֵ
	const double epsilon = std::numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	// flagΪ�ٹ����˹�������X
	if (!flag)
		return z1 * sigma + mu;
	double u1, u2;
	// �����������
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	// flagΪ�湹���˹�������X
	z0 = sqrt(-2.0 * log(u1)) * cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(2 * CV_PI * u2);
	return z0 * sigma + mu;
}
// ͼ����Ӹ�˹����
cv::Mat addGaussianNoise(cv::Mat& srcImage)
{
	cv::Mat resultImage = srcImage.clone();
	int channels = resultImage.channels();
	int nRows = resultImage.rows;
	int nCols = resultImage.cols * channels;
	// �ж�ͼ���������
	if (resultImage.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j){
			// ��Ӹ�˹����
			int val = resultImage.ptr<uchar>(i)[j] +
				generateGaussianNoise(2, 0.8) * 32;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			resultImage.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return resultImage;
}
int main()
{
	cv::Mat srcImage =
		cv::imread("..\\images\\flower3.jpg", 1);
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat resultImage = addGaussianNoise(srcImage);
	cv::imshow("resultIamge", resultImage);
	cv::waitKey(0);
	return 0;
}
