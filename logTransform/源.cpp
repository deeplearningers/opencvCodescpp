// ���ܣ����� 3-22 �����任������ʵ�ַ���
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
// �����任����1
cv::Mat logTransform1(cv::Mat srcImage, int c)
{
	// ����ͼ���ж�
	if (srcImage.empty())
		std::cout << "No data!" << std::endl;
	cv::Mat resultImage =
		cv::Mat::zeros(srcImage.size(), srcImage.type());
	// ���� 1 + r
	cv::add(srcImage, cv::Scalar(1.0), srcImage);
	// ת��Ϊ32λ������
	srcImage.convertTo(srcImage, CV_32F);
	// ���� log(1 + r)
	log(srcImage, resultImage);
	resultImage = c * resultImage;
	// ��һ������
	cv::normalize(resultImage, resultImage,
		0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(resultImage, resultImage);
	return resultImage;
}
// �����任����2
cv::Mat logTransform2(Mat srcImage, float c)
{
	// ����ͼ���ж�
	if (srcImage.empty())
		std::cout << "No data!" << std::endl;
	cv::Mat resultImage =
		cv::Mat::zeros(srcImage.size(), srcImage.type());
	double gray = 0;
	// ͼ������ֱ����ÿ�����ص�Ķ����任  
	for (int i = 0; i < srcImage.rows; i++){
		for (int j = 0; j < srcImage.cols; j++){
			gray = (double)srcImage.at<uchar>(i, j);
			gray = c*log((double)(1 + gray));
			resultImage.at<uchar>(i, j) = saturate_cast<uchar>(gray);
		}
	}
	// ��һ������
	cv::normalize(resultImage, resultImage,
		0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(resultImage, resultImage);
	return resultImage;
}
// �����任����3
cv::Mat logTransform3(Mat srcImage, float c)
{
	// ����ͼ���ж�
	if (srcImage.empty())
		std::cout << "No data!" << std::endl;
	cv::Mat resultImage =
		cv::Mat::zeros(srcImage.size(), srcImage.type());
	srcImage.convertTo(resultImage, CV_32F);
	resultImage = resultImage + 1;
	cv::log(resultImage, resultImage);
	resultImage = c * resultImage;
	cv::normalize(resultImage, resultImage, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(resultImage, resultImage);
	return resultImage;
}
int main()
{
	// ��ȡ�Ҷ�ͼ����֤
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg", 0);
	if (!srcImage.data)
		return -1;
	// ��֤���ֲ�ͬ��ʽ�Ķ����任�ٶ�
	cv::imshow("srcImage", srcImage);
	float c = 1.1;
	cv::Mat resultImage;
	double tTime;
	tTime = (double)getTickCount();
	const int nTimes = 100;
	for (int i = 0; i < nTimes; i++)
	{
		resultImage = logTransform3(srcImage, c);
	}
	tTime = 1000 * ((double)getTickCount() - tTime) /
		getTickFrequency();
	tTime /= nTimes;
	std::cout << tTime << std::endl;
	cv::imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
