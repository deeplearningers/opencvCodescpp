// ���ܣ����� 3-26 �������ֵ�ָ�
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
// ���㵱ǰ��λ�õ�������
float caculateCurrentEntropy(cv::Mat hist, int threshold)
{
	float BackgroundSum = 0, targetSum = 0;
	const float* pDataHist = (float*)hist.ptr<float>(0);
	for (int i = 0; i < 256; i++)
	{
		// �ۼƱ���ֵ
		if (i < threshold)
		{
			BackgroundSum += pDataHist[i];
		}
		else // �ۼ�Ŀ��ֵ
		{
			targetSum += pDataHist[i];
		}
	}
	//std::cout << BackgroundSum << " "<< targetSum << std::endl;
	float BackgroundEntropy = 0, targetEntropy = 0;
	for (int i = 0; i < 256; i++)
	{
		// ���㱳����
		if (i < threshold)
		{
			if (pDataHist[i] == 0)
				continue;
			float ratio1 = pDataHist[i] / BackgroundSum;
			// ���㵱ǰ������
			BackgroundEntropy += -ratio1 * logf(ratio1);
		}
		else // ����Ŀ����
		{
			if (pDataHist[i] == 0)
				continue;
			float ratio2 = pDataHist[i] / targetSum;
			targetEntropy += -ratio2 * logf(ratio2);
		}
	}
	return (targetEntropy + BackgroundEntropy);
}
// Ѱ���������ֵ���ָ�
cv::Mat maxEntropySegMentation(cv::Mat inputImage)
{
	// ��ʼ��ֱ��ͼ����
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float pranges[2] = { 0, 256 };
	const float* ranges[1] = { pranges };
	cv::MatND hist;
	// ����ֱ��ͼ
	cv::calcHist(&inputImage, 1, channels,
		cv::Mat(), hist, 1, histSize, ranges);
	float maxentropy = 0;
	int    max_index = 0;
	cv::Mat result;
	// �����õ��������ֵ�ָ�������ֵ
	for (int i = 0; i < 256; i++)
	{
		float cur_entropy =
			caculateCurrentEntropy(hist, i);
		// ���㵱ǰ���ֵ��λ��
		if (cur_entropy > maxentropy)
		{
			maxentropy = cur_entropy;
			max_index = i;
		}
	}
	//  ��ֵ���ָ�
	threshold(inputImage, result, max_index, 255,
		CV_THRESH_BINARY);
	return result;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\hand1.jpg");
	if (!srcImage.data)
		return 0;
	cv::Mat grayImage;
	cv::cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	// �������ֵ�ָ�ʵ��    
	cv::Mat result = maxEntropySegMentation(grayImage);
	cv::imshow("grayImage", grayImage);
	cv::imshow("result", result);
	cv::waitKey(0);
	return 0;
}
