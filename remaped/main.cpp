// ���ܣ����� 2-8 remap ��ӳ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg");
	if (!srcImage.data)
		return -1;
	// ���������
	cv::Mat resultImage(srcImage.size(), srcImage.type());
	// X��Y�������
	cv::Mat xMapImage(srcImage.size(), CV_32FC1);
	cv::Mat yMapImage(srcImage.size(), CV_32FC1);
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			// x��y����ת
			xMapImage.at<float>(j, i) = cols - i;
			yMapImage.at<float>(j, i) = rows - j;
		}
	}
	// ��ӳ�����
	remap(srcImage, resultImage, xMapImage, yMapImage,
		CV_INTER_LINEAR, cv::BORDER_CONSTANT,
		cv::Scalar(0, 0, 0));
	// ������
	cv::imshow("srcImage", srcImage);
	cv::imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
