// ���ܣ����� 3-23 �Աȶ�����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream>  
cv::Mat contrastStretch(cv::Mat srcImage)
{
	cv::Mat resultImage = srcImage.clone();
	int nRows = resultImage.rows;
	int nCols = resultImage.cols;
	// ͼ���������ж�
	if (resultImage.isContinuous())
	{
		nCols = nCols  * nRows;
		nRows = 1;
	}
	// ͼ��ָ�����
	uchar *pDataMat;
	int pixMax = 0, pixMin = 255;
	// ����ͼ��������Сֵ
	for (int j = 0; j < nRows; j++)
	{
		pDataMat = resultImage.ptr<uchar>(j);
		for (int i = 0; i < nCols; i++)
		{
			if (pDataMat[i] > pixMax)
				pixMax = pDataMat[i];
			if (pDataMat[i] < pixMin)
				pixMin = pDataMat[i];
		}
	}
	// �Աȶ�����ӳ��
	for (int j = 0; j < nRows; j++)
	{
		pDataMat = resultImage.ptr<uchar>(j);
		for (int i = 0; i < nCols; i++)
		{
			pDataMat[i] = (pDataMat[i] - pixMin) *
				255 / (pixMax - pixMin);
		}
	}
	return resultImage;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\img07.JPG");
	if (!srcImage.data)
		return 0;
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	imshow("srcGray", srcGray);
	cv::Mat resultImage = contrastStretch(srcGray);
	cv::imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
