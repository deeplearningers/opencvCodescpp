// ���ܣ����� 3-14 ֱ��ͼƥ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	// ����Դͼ����ʾ
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	cv::Mat dstImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data || !dstImage.data)
		return 1;
	cv::resize(dstImage, dstImage, cv::Size(srcImage.rows, srcImage.cols), 0, 0, CV_INTER_LINEAR);
	cv::imshow("srcImage", srcImage);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	//��ʼ���ۼƷֲ�����
	float srcCdfArr[256];
	float dstCdfArr[256];
	int srcAddTemp[256];
	int dstAddTemp[256];
	int histMatchMap[256];
	for (int i = 0; i < 256; i++){
		srcAddTemp[i] = 0;
		dstAddTemp[i] = 0;
		srcCdfArr[i] = 0;
		dstCdfArr[i] = 0;
		histMatchMap[i] = 0;
	}
	float sumSrcTemp = 0;
	float sumDstTemp = 0;
	int nSrcPix = srcImage.cols * srcImage.rows;
	int nDstPix = dstImage.cols * dstImage.rows;
	int matchFlag = 0;
	// ���Դͼ����Ŀ��ͼ����ۻ�ֱ��ͼ
	for (size_t nrow = 0; nrow < srcImage.rows; nrow++)
	for (size_t ncol = 0; ncol < srcImage.cols; ncol++)
	{
		srcAddTemp[(int)srcImage.at<uchar>(nrow, ncol)]++;
		dstAddTemp[(int)dstImage.at<uchar>(nrow, ncol)]++;
	}
	// ���Դͼ����Ŀ��ͼ����ۻ����ʷֲ�
	for (int i = 0; i < 256; i++)
	{
		sumSrcTemp += srcAddTemp[i];
		srcCdfArr[i] = sumSrcTemp / nSrcPix;//Դͼ�����ص��ۼƸ��ʷֲ�
		sumDstTemp += dstAddTemp[i];
		dstCdfArr[i] = sumDstTemp / nDstPix;//Ŀ��ͼ�����ص��ۼƸ��ʷֲ�
	}
	// ֱ��ͼƥ��ʵ��
	for (int i = 0; i < 256; i++)
	{
		float minMatchPara = 20;//��ֵ
		for (int j = 0; j< 256; j++)
		{
			// �жϵ�ǰֱ��ͼ�ۼƲ���
			if (minMatchPara > abs(srcCdfArr[i] - dstCdfArr[j]))
			{
				minMatchPara = abs(srcCdfArr[i] - dstCdfArr[j]);
				matchFlag = j;
			}
		}
		histMatchMap[i] = matchFlag;
	}
	// ��ʼ��ƥ��ͼ��
	cv::Mat HistMatchImage =
		cv::Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	cv::cvtColor(srcImage, HistMatchImage, CV_BGR2GRAY);
	// ͨ��mapӳ���ƥ��ͼ��
	for (int i = 0; i < HistMatchImage.rows; i++)
	for (int j = 0; j < HistMatchImage.cols; j++)
	{
		HistMatchImage.at<uchar>(i, j) =
			histMatchMap[(int)HistMatchImage.at<uchar>(i, j)];
	}

	cv::imshow("resultImage", HistMatchImage);
	cv::waitKey(0);
	return 0;
}
