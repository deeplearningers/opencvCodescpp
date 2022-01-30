// ���ܣ����� 3-24 �Ҷȼ��ֲ�
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream>  
cv::Mat grayLayered(cv::Mat srcImage)
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
	int controlMin = 100;
	int controlMax = 200;
	// ����ͼ��ĻҶȼ��ֲ�
	for (int j = 0; j < nRows; j++)
	{
		pDataMat = resultImage.ptr<uchar>(j);
		for (int i = 0; i < nCols; i++)
		{
			// ��һ�ַ��� ��ֵӳ��
			/*if (pDataMat[i] > controlMin)
				pDataMat[i] = 255;
				else
				pDataMat[i] = 0;*/
			 // �ڶ��ַ��� ����ӳ��
			 if(pDataMat[i] > controlMin && 
			 	pDataMat[i] < controlMax)       
			 	pDataMat[i] = controlMax;
		}
	}
	return resultImage;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg");
	if (!srcImage.data)
		return 0;
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	imshow("srcGray", srcGray);
	cv::Mat resultImage = grayLayered(srcGray);
	cv::imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
