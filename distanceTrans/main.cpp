// ���ܣ����� 3-18 ����任ɨ��ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
// ����ŷʽ����
float calcEuclideanDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(float((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}
// �������̾���
int calcChessboardDistance(int x1, int y1, int x2, int y2)
{
	return cv::max(abs(x1 - x2), abs(y1 - y2));
}
// �����������
int calcBlockDistance(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}
// ����任����ʵ��
void distanceTrans(cv::Mat &srcImage, cv::Mat &resultIamge)
{
	CV_Assert(srcImage.data != NULL);
	cv::Mat srcGray, srcBinary;
	// ת���ɻҶ�ͼ��
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	// ת���ɶ�ֵͼ��
	threshold(srcGray, srcBinary, 100, 255, cv::THRESH_BINARY);
	cv::imshow("srcBinary", srcBinary);
	int rows = srcBinary.rows;
	int cols = srcBinary.cols;
	uchar* pDataOne;
	uchar* pDataTwo;
	float disPara = 0;
	float fDisMin = 0;
	// ��һ�����ͼ������ģ���������ֵ
	for (int i = 1; i < rows - 1; i++)
	{
		// ͼ��ָ���ȡ
		pDataOne = srcBinary.ptr<uchar>(i);
		for (int j = 1; j < cols; j++)
		{
			// �ֱ��������ģ��������ؾ���
			//   pL  pL
			//   pL  p
			//   pL
			pDataTwo = srcBinary.ptr<uchar>(i - 1);
			disPara = calcEuclideanDistance(i, j, i - 1, j - 1);
			fDisMin = cv::min((float)pDataOne[j],
				disPara + pDataTwo[j - 1]);
			disPara = calcEuclideanDistance(i, j, i - 1, j);
			fDisMin = cv::min(fDisMin,
				disPara + pDataTwo[j]);
			pDataTwo = srcBinary.ptr<uchar>(i);
			disPara = calcEuclideanDistance(i, j, i, j - 1);
			fDisMin = cv::min(fDisMin,
				disPara + pDataTwo[j - 1]);
			pDataTwo = srcBinary.ptr<uchar>(i + 1);
			disPara = calcEuclideanDistance(i, j, i + 1, j - 1);
			fDisMin = cv::min(fDisMin,
				disPara + pDataTwo[j - 1]);
			pDataOne[j] = (uchar)cvRound(fDisMin);
		}
	}
	// �ڶ������ͼ������ģ���������ֵ
	for (int i = rows - 2; i > 0; i--)
	{
		pDataOne = srcBinary.ptr<uchar>(i);
		for (int j = cols - 1; j >= 0; j--)
		{
			// �ֱ��������ģ��������ؾ��� 
			//   pR  pR
			//   pR  p
			//   pR     
			pDataTwo = srcBinary.ptr<uchar>(i + 1);
			disPara = calcEuclideanDistance(i, j, i + 1, j);
			fDisMin = cv::min((float)pDataOne[j],
				disPara + pDataTwo[j]);
			disPara = calcEuclideanDistance(i, j, i + 1, j + 1);
			fDisMin = cv::min(fDisMin,
				disPara + pDataTwo[j + 1]);
			pDataTwo = srcBinary.ptr<uchar>(i);
			disPara = calcEuclideanDistance(i, j, i, j + 1);
			fDisMin = cv::min(fDisMin,
				disPara + pDataTwo[j + 1]);
			pDataTwo = srcBinary.ptr<uchar>(i - 1);
			disPara = calcEuclideanDistance(i, j, i - 1, j + 1);
			fDisMin = cv::min(fDisMin,
				disPara + pDataTwo[j + 1]);
			pDataOne[j] = (uchar)cvRound(fDisMin);
		}
	}
	resultIamge = srcBinary.clone();
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return -1;
	cv::Mat resultIamge;
	distanceTrans(srcImage, resultIamge);
	cv::imshow("resultIamge", resultIamge);
	cv::waitKey(0);
	return 0;
}
