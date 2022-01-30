// ���ܣ����� 4-6 ͼ����Ҷ�任
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
cv::Mat DFT(cv::Mat srcImage)
{
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	// ������ͼ����������ѵĳߴ�
	int nRows = getOptimalDFTSize(srcGray.rows);
	int nCols = getOptimalDFTSize(srcGray.cols);
	cv::Mat resultImage;
	// �ѻҶ�ͼ��������Ͻ�,���ұߺ��±���չͼ��,
	// ��ӵ����س�ʼ��Ϊ0
	copyMakeBorder(srcGray, resultImage, 0,
		nRows - srcGray.rows,
		0, nCols - srcGray.cols,
		BORDER_CONSTANT, Scalar::all(0));//top,bottom,left,right
	// Ϊ����Ҷ�任�Ľ��(ʵ�����鲿)����洢�ռ�
	cv::Mat planes[] = { cv::Mat_<float>(resultImage),
		cv::Mat::zeros(resultImage.size(), CV_32F) };
	Mat completeI;
	// Ϊ�������ͼ������һ����ʼ��Ϊ0��ͨ��
	merge(planes, 2, completeI);
	// ������ɢ����Ҷ�任
	dft(completeI, completeI);
	// ������ת��Ϊ����
	split(completeI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	cv::Mat dftResultImage = planes[0];
	// �����߶�(logarithmic scale)����
	dftResultImage += 1;
	log(dftResultImage, dftResultImage);
	// ���к��طֲ�����ͼ����
	dftResultImage = dftResultImage(Rect(0,
		0, srcGray.cols, srcGray.rows));
	// ��һ��ͼ��
	normalize(dftResultImage, dftResultImage,
		0, 1, CV_MINMAX);
	int cx = dftResultImage.cols / 2;
	int cy = dftResultImage.rows / 2;
	Mat tmp;
	// Top-Left - Ϊÿһ�����޴���ROI
	Mat q0(dftResultImage, Rect(0, 0, cx, cy));
	// Top-Right
	Mat q1(dftResultImage, Rect(cx, 0, cx, cy));
	// Bottom-Left
	Mat q2(dftResultImage, Rect(0, cy, cx, cy));
	// Bottom-Right
	Mat q3(dftResultImage, Rect(cx, cy, cx, cy));
	// �������� (Top-Left with Bottom-Right)    
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	// �������� (Top-Right with Bottom-Left)
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	return dftResultImage;
}
int main()
{
	cv::Mat srcImage = imread("..\\images\\hand3.jpg");
	if (srcImage.empty())
		return-1;
	imshow("srcImage", srcImage);
	cv::Mat resultImage = DFT(srcImage);
	imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
