// ���ܣ����� 7-4 ��ֵƯ��ͼ��ָ�
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
//��ɫͨ������
static void MergeSeg(Mat& img
	, const Scalar& colorDiff = Scalar::all(1))
{
	CV_Assert(!img.empty());
	RNG rng = theRNG();
	// ��������ͼ��
	Mat mask(img.rows + 2, img.cols + 2,
		CV_8UC1, Scalar::all(0));
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			if (mask.at<uchar>(y + 1, x + 1) == 0)
			{
				// ��ɫ����
				Scalar newVal(rng(256), rng(256), rng(256));
				// ����ϲ�
				floodFill(img, mask, Point(x, y)
					, newVal, 0, colorDiff, colorDiff);
			}
		}
	}
}
int main(int argc, char** argv)
{
	cv::Mat srcImg = imread("..\\images\\sea.jpg");
	if (srcImg.empty())
		return -1;
	// �����趨
	int spatialRad = 20;
	int colorRad = 20;
	int maxPyrLevel = 6;
	cv::Mat resImg;
	// ��ֵƯ�Ʒָ�
	pyrMeanShiftFiltering(srcImg, resImg,
		spatialRad, colorRad, maxPyrLevel);
	// ��ɫͨ������ϲ�
	MergeSeg(resImg, Scalar::all(2));
	cv::imshow("src", srcImg);
	cv::imshow("resImg", resImg);
	cv::waitKey();
	return 0;
}
