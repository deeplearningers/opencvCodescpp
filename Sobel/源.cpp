// ���ܣ����� 5-2-5 Sobel ��Եʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
// �Ǽ���ֵ����ʵ��sobel��ֱϸ����Ե
bool SobelVerEdge(cv::Mat srcImage, cv::Mat& resultImage)
{
	CV_Assert(srcImage.channels() == 1);
	srcImage.convertTo(srcImage, CV_32FC1);
	// ˮƽ����� Sobel ����
	cv::Mat sobelx = (cv::Mat_<float>(3, 3) << -0.125, 0, 0.125,
		-0.25, 0, 0.25,
		-0.125, 0, 0.125);
	cv::Mat ConResMat;
	// �������
	cv::filter2D(srcImage, ConResMat, srcImage.type(), sobelx);
	// �����ݶȵķ���
	cv::Mat graMagMat;
	cv::multiply(ConResMat, ConResMat, graMagMat);
	// �����ݶȷ��ȼ�����������ֵ
	int scaleVal = 4;
	double thresh = scaleVal * cv::mean(graMagMat).val[0];
	cv::Mat resultTempMat = cv::Mat::zeros(
		graMagMat.size(), graMagMat.type());
	float* pDataMag = (float*)graMagMat.data;
	float* pDataRes = (float*)resultTempMat.data;
	const int nRows = ConResMat.rows;
	const int nCols = ConResMat.cols;
	for (int i = 1; i != nRows - 1; ++i) {
		for (int j = 1; j != nCols - 1; ++j) {
			// ����õ��ݶ���ˮƽ��ֱ�ݶ�ֵ��С�ȽϽ��
			bool b1 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j - 1]);
			bool b2 = (pDataMag[i * nCols + j] > pDataMag[i * nCols + j + 1]);
			bool b3 = (pDataMag[i * nCols + j] > pDataMag[(i - 1) * nCols + j]);
			bool b4 = (pDataMag[i * nCols + j] > pDataMag[(i + 1) * nCols + j]);
			// �ж������ݶ��Ƿ��������ˮƽ��ֱ�ݶ�
			// ����������Ӧ��ֵ�������ж�ֵ��
			pDataRes[i * nCols + j] = 255 * ((pDataMag[i * nCols + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	resultTempMat.convertTo(resultTempMat, CV_8UC1);
	resultImage = resultTempMat.clone();
	return true;
}

// ͼ��ֱ�Ӿ��ʵ��sobel
bool sobelEdge(const cv::Mat&  srcImage, cv::Mat& resultImage, uchar threshold)
{
	CV_Assert(srcImage.channels() == 1);
	// ��ʼ��ˮƽ������
	Mat sobelx = (Mat_<double>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);
	// ��ʼ����ֱ������
	Mat sobely = (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
	resultImage = Mat::zeros(srcImage.rows - 1,
		srcImage.cols - 1, srcImage.type());
	double edgeX = 0;
	double edgeY = 0;
	double graMag = 0;
	for (int k = 1; k < srcImage.rows - 1; ++k) {
		for (int n = 1; n < srcImage.cols - 1; ++n) {
			edgeX = 0;
			edgeY = 0;
			// ��������ˮƽ�봹ֱ�ݶ�
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					edgeX += srcImage.at<uchar>(k + i, n + j) *
						sobelx.at<double>(1 + i, 1 + j);
					edgeY += srcImage.at<uchar>(k + i, n + j) *
						sobely.at<double>(1 + i, 1 + j);
				}
			}
			// �����ݶ�ģ��
			graMag = sqrt(pow(edgeY, 2) + pow(edgeX, 2));
			// ��ֵ��
			resultImage.at<uchar>(k , n ) =
				((graMag > threshold) ? 255 : 0);
		}
	}
	return true;
}
// ͼ����ʵ��sobel �Ǽ���ֵ����
bool sobelOptaEdge(const cv::Mat& srcImage, cv::Mat& resultImage, int flag)
{
	CV_Assert(srcImage.channels() == 1);
	// ��ʼ��sobelˮƽ������
	cv::Mat sobelX = (cv::Mat_<double>(3, 3) << 1, 0, -1,
		2, 0, -2,
		1, 0, -1);
	// ��ʼ��sebel��ֱ������
	cv::Mat sobelY = (cv::Mat_<double>(3, 3) << 1, 2, 1,
		0, 0, 0,
		-1, -2, -1);
	// ����ˮƽ�봹ֱ���
	cv::Mat edgeX, edgeY;
	filter2D(srcImage, edgeX, CV_32F, sobelX);
	filter2D(srcImage, edgeY, CV_32F, sobelY);
	// ���ݴ������ȷ������ˮƽ��ֱ��Ե
	int paraX = 0;
	int paraY = 0;
	switch (flag)
	{
	case 0: paraX = 1;
		paraY = 0;
		break;
	case 1:  paraX = 0;
		paraY = 1;
		break;
	case 2:  paraX = 1;
		paraY = 1;
		break;
	default: break;
	}
	edgeX = abs(edgeX);
	edgeY = abs(edgeY);
	cv::Mat graMagMat = paraX * edgeX.mul(edgeX) + paraY * edgeY.mul(edgeY);
	// ������ֵ 
	int scaleVal = 4;
	double thresh = scaleVal * cv::mean(graMagMat).val[0];
	resultImage = cv::Mat::zeros(srcImage.size(), srcImage.type());
	for (int i = 1; i < srcImage.rows - 1; i++)
	{
		float* pDataEdgeX = edgeX.ptr<float>(i);
		float* pDataEdgeY = edgeY.ptr<float>(i);
		float* pDataGraMag = graMagMat.ptr<float>(i);
		// ��ֵ���ͼ���ֵ����
		for (int j = 1; j < srcImage.cols - 1; j++)
		{
			if (pDataGraMag[j] > thresh && (
				(pDataEdgeX[j] > paraX * pDataEdgeY[j] && pDataGraMag[j] >
				pDataGraMag[j - 1] && pDataGraMag[j] > pDataGraMag[j + 1]) ||
				(pDataEdgeY[j] > paraY * pDataEdgeX[j] && pDataGraMag[j] >
				pDataGraMag[j - 1] && pDataGraMag[j] > pDataGraMag[j + 1])))
				resultImage.at<uchar>(i, j) = 255;
		}
	}
	return true;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\building.jpg", 0);
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat resultImage;
	// �Ǽ���ֵ����ϸ����ֱsobel���
	SobelVerEdge(srcImage, resultImage);
	cv::imshow("resultImage", resultImage);
	cv::Mat resultImage2;
	// ͼ��ֱ�Ӿ��ʵ��sobel���
	sobelEdge(srcImage, resultImage2, 100);
	cv::imshow("resultImage2", resultImage2);
	cv::Mat resultImage3;
	int flag = 2;
	// ͼ�����·Ǽ���ֵ����
	sobelOptaEdge(srcImage, resultImage3, 2);
	cv::imshow("resultImage3", resultImage3);
	cv::waitKey(0);
	return 0;
}