// ���ܣ����� 3-27 ����ͼ�񲨷��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
// ����ͼ��Ĳ���
void findPeak(cv::Mat srcImage, vector<int>& resultVec)
{
	cv::Mat verMat;
	cv::Mat resMat = srcImage.clone();
	// ��ֵ������
	int thresh = 130;
	int threshType = 0;
	// Ԥ�����ֵ
	const int maxVal = 255;
	// �̶���ֵ������
	cv::threshold(srcImage, srcImage, thresh,
		maxVal, threshType);
	srcImage.convertTo(srcImage, CV_32FC1);
	// ���㴹ֱͶӰ
	cv::reduce(srcImage, verMat, 0, CV_REDUCE_SUM);
	// std::cout << verMat << std::endl;
	// �������ַ��ź���
	float* iptr = ((float*)verMat.data) + 1;
	vector<int> tempVec(verMat.cols - 1, 0);
	for (int i = 1; i < verMat.cols - 1; ++i, ++iptr)
	{
		if (*(iptr + 1) - *iptr >0)//һ�ײ���жϷ���
			tempVec[i] = 1;
		else if (*(iptr + 1) - *iptr < 0)
			tempVec[i] = -1;
		else
			tempVec[i] = 0;
	}
	// �Է��ź��������������--����tempVec
	for (int i = tempVec.size() - 1; i >= 0; i--)
	{
		if (tempVec[i] == 0 && i == tempVec.size() - 1)
		{
			tempVec[i] = 1;
		}
		else if (tempVec[i] == 0)
		{
			if (tempVec[i + 1] >= 0)
				tempVec[i] = 1;
			else
				tempVec[i] = -1;
		}
	}
	// �����ж����
	for (vector<int>::size_type i = 0; i != tempVec.size() - 1; i++)
	{
		if (tempVec[i + 1] - tempVec[i] == -2)
			resultVec.push_back(i + 1);
	}
	// �������λ��
	for (int i = 0; i < resultVec.size(); i++)
	{
		std::cout << resultVec[i] << " ";
		//resMat.at(resultVec[i], resultVec[i]) = 255;
		for (int ii = 0; ii < resMat.rows; ++ii)
		{
			resMat.at<uchar>(ii, resultVec[i]) = 255;
		}
	}
	imshow("resMat", resMat);
}
int main()
{
	cv::Mat image = imread("..\\images\\test.jpg", 0);
	if (!image.data)
		return 0;
	imshow("Image", image);
	vector<int> resultVec;
	findPeak(image, resultVec);
	cv::waitKey(0);
	return 0;
}
