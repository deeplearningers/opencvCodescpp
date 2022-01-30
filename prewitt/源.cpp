// ���ܣ����� 5-9 Prewitt ��Ե���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
// prewitt����ʵ��
cv::Mat prewitts(cv::Mat img, bool verFlag = false)
{
	img.convertTo(img, CV_32FC1);
	cv::Mat prewitt_kernel =
		(cv::Mat_<float>(3, 3) << 0.1667, 0.1667, 0.1667,
		0, 0, 0,
		-0.1667, -0.1667, -0.1667);
	// ˮƽ��Ե
	if (verFlag) {
		prewitt_kernel = prewitt_kernel.t();
		cv::Mat z1 = cv::Mat::zeros(img.rows, 1, CV_32FC1);
		cv::Mat z2 = cv::Mat::zeros(1, img.cols, CV_32FC1);
		// ��ͼ����ı���Ϊ 0 
		z1.copyTo(img.col(0));
		z1.copyTo(img.col(img.cols - 1));
		z2.copyTo(img.row(0));
		z2.copyTo(img.row(img.rows - 1));
	}
	cv::Mat edges;
	cv::filter2D(img, edges, img.type(), prewitt_kernel);
	cv::Mat mag;
	cv::multiply(edges, edges, mag);
	// ˮƽ��Ե�߽�ڱ�ȥ��
	if (verFlag)
	{
		cv::Mat black_region = img < 0.03;
		cv::Mat se = cv::Mat::ones(5, 5, CV_8UC1);
		cv::dilate(black_region, black_region, se);
		mag.setTo(0, black_region);
	}
	// ����ģ������ݶȵ���ֵ
	double thresh = 4.0f * cv::mean(mag).val[0];
	// ����ĳ���ݶȴ���ˮƽ�����
	// ��ֱ�����ڵ��ݶ�ʱ�����λ�����ֵΪ 255
	// ��Ӧ����ֵthresh
	cv::Mat dstImage = cv::Mat::zeros(mag.size(), mag.type());
	float* dptr = (float*)mag.data;
	float* tptr = (float*)dstImage.data;
	int r = edges.rows, c = edges.cols;
	for (int i = 1; i != r - 1; ++i)
	{
		for (int j = 1; j != c - 1; ++j)
		{
			// �Ǽ���ֵ����
			bool b1 = (dptr[i * c + j] > dptr[i * c + j - 1]);
			bool b2 = (dptr[i * c + j] > dptr[i * c + j + 1]);
			bool b3 = (dptr[i * c + j] > dptr[(i - 1) * c + j]);
			bool b4 = (dptr[i * c + j] > dptr[(i + 1) * c + j]);
			tptr[i * c + j] = 255 * ((dptr[i * c + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	dstImage.convertTo(dstImage, CV_8UC1);
	return dstImage;
}
int main()
{
	cv::Mat srcImage =
		cv::imread("..\\images\\building.jpg", 0);
	if (!srcImage.data)
		return -1;
	cv::Mat dstImage = prewitts(srcImage);
	cv::imshow("srcImage", srcImage);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
