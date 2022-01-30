// ���ܣ����� 6-5 ��̬ѧ�˲�ʵ�ֽǵ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	// ����ṹԪ��
	Mat CrossMat(5, 5, CV_8U, Scalar(0));
	Mat diamondMat(5, 5, CV_8U, Scalar(1));
	Mat squareMat(5, 5, CV_8U, Scalar(1));
	Mat x(5, 5, CV_8U, Scalar(0));
	//  ʮ������״  
	for (int i = 0; i < 5; i++)
	{
		CrossMat.at<uchar>(2, i) = 1;
		CrossMat.at<uchar>(i, 2) = 1;
	}
	// ������״
	diamondMat.at<uchar>(0, 0) = 0;
	diamondMat.at<uchar>(0, 1) = 0;
	diamondMat.at<uchar>(1, 0) = 0;
	diamondMat.at<uchar>(4, 4) = 0;
	diamondMat.at<uchar>(3, 4) = 0;
	diamondMat.at<uchar>(4, 3) = 0;
	diamondMat.at<uchar>(4, 0) = 0;
	diamondMat.at<uchar>(4, 1) = 0;
	diamondMat.at<uchar>(3, 0) = 0;
	diamondMat.at<uchar>(0, 4) = 0;
	diamondMat.at<uchar>(0, 3) = 0;
	diamondMat.at<uchar>(1, 4) = 0;
	// X��״
	for (int i = 0; i < 5; i++){
		x.at<uchar>(i, i) = 1;
		x.at<uchar>(4 - i, i) = 1;
	}
	// ��1����ʮ���ζ�ԭͼ��������
	Mat result;
	dilate(srcGray, result, CrossMat);
	// ��2�������ζ��ϲ����и�ʴ
	erode(result, result, diamondMat);
	Mat result2;
	// ��3����X�ζ�ԭͼ���и�ʴ
	dilate(srcGray, result2, x);
	// ��4���������ζ��ϲ����и�ʴ
	erode(result2, result2, squareMat);
	// ��4���������ֵ
	absdiff(result2, result, result);
	threshold(result, result, 40, 255, THRESH_BINARY);
	// ��ͼ
	for (int i = 0; i < result.rows; i++)
	{
		// ��ȡ��ָ��
		const uchar* data = result.ptr<uchar>(i);
		for (int j = 0; j < result.cols; j++)
		{
			// ����ǽǵ� ����л���ԲȦ
			if (data[j])
				circle(srcImage, Point(j, i),4,
				Scalar(0, 255, 0));
		}
	}
	cv::imshow("result", result);
	cv::imshow("srcImage", srcImage);
	cv::waitKey(0);
	return 0;
}
