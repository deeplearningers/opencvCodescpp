// ���ܣ����� 4-5 ͼ���������������ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
#include <stdio.h>
using namespace cv;
using namespace std;
// �������������������
cv::Mat Myfilter2D(cv::Mat srcImage)
{
	const int nChannels = srcImage.channels();
	cv::Mat resultImage(srcImage.size(), srcImage.type());
	for (int j = 1; j < srcImage.rows - 1; ++j)
	{
		// ��ȡ����ָ��
		const uchar* previous = srcImage.ptr<uchar>(j - 1);
		const uchar* current = srcImage.ptr<uchar>(j);
		const uchar* next = srcImage.ptr<uchar>(j + 1);
		uchar* output = resultImage.ptr<uchar>(j);
		for (int i = nChannels; i < nChannels*(srcImage.cols - 1); ++i)
		{
			// 4-�����ֵ������� 
			*output++ = saturate_cast<uchar>(
				(current[i - nChannels] + current[i + nChannels] +
				previous[i] + next[i]) / 4);
		}
	}
	// �߽紦��
	resultImage.row(0).setTo(Scalar(0));
	resultImage.row(resultImage.rows - 1).setTo(Scalar(0));
	resultImage.col(0).setTo(Scalar(0));
	resultImage.col(resultImage.cols - 1).setTo(Scalar(0));
	return resultImage;
}
// �Դ����������
cv::Mat filter2D_(cv::Mat srcImage)
{
	cv::Mat resultImage(srcImage.size(), srcImage.type());
	Mat kern = (Mat_<float>(3, 3) << 0, 1, 0,
		1, 0, 1,
		0, 1, 0) / (float)(4);
	filter2D(srcImage, resultImage, srcImage.depth(), kern);
	return resultImage;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return 0;
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	imshow("srcGray", srcGray);
	cv::Mat resultImage = Myfilter2D(srcGray);
	imshow("resultImage", resultImage);
	cv::Mat resultImage2 = filter2D_(srcGray);
	imshow("resultImage2", resultImage2);
	cv::waitKey(0);
	return 0;
}
