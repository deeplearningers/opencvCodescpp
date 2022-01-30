// ���ܣ����� 3-20 Gamma У��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
using namespace std;
using namespace cv;
// Gamma�任����ʵ��
cv::Mat gammaTransform(cv::Mat& srcImage, float kFactor)
{
	// ��������ļ�LUT
	unsigned char LUT[256];
	for (int i = 0; i < 256; i++)
	{
		// Gamma�任���ʽ
		LUT[i] = saturate_cast<uchar>(pow((float)(
			i / 255.0), kFactor) * 255.0f);
	}
	cv::Mat resultImage = srcImage.clone();
	// ����ͨ��Ϊ��ͨ��ʱ ֱ�ӽ��б任
	if (srcImage.channels() == 1)
	{
		cv::MatIterator_<uchar> iterator =
			resultImage.begin<uchar>();
		cv::MatIterator_<uchar> iteratorEnd =
			resultImage.end<uchar>();
		for (; iterator != iteratorEnd; iterator++)
			*iterator = LUT[(*iterator)];
	}
	else
	{
		// ����ͨ��Ϊ��ͨ��ʱ ���ÿ��ͨ���ֱ���б任
		cv::MatIterator_<cv::Vec3b> iterator =
			resultImage.begin<Vec3b>();
		cv::MatIterator_<cv::Vec3b> iteratorEnd =
			resultImage.end<Vec3b>();
		//  ͨ�����ұ����ת��
		for (; iterator != iteratorEnd; iterator++)
		{
			(*iterator)[0] = LUT[((*iterator)[0])];
			(*iterator)[1] = LUT[((*iterator)[1])];
			(*iterator)[2] = LUT[((*iterator)[2])];
		}
	}
	return resultImage;
}
int main()
{
	cv::Mat srcImage = imread("..\\images\\lakeWater.jpg");
	if (!srcImage.data)
		return -1;
	// ��ʼ�����ֲ�ͬ���� �Աȷ���Ч��
	float kFactor1 = 0.3;
	float kFactor2 = 3.0;
	cv::Mat result1 = gammaTransform(srcImage, kFactor1);
	cv::Mat result2 = gammaTransform(srcImage, kFactor2);
	cv::imshow("srcImage", srcImage);
	cv::imshow("result1", result1);
	cv::imshow("result2", result2);
	cv::waitKey(0);
	return 0;
}
