// ���ܣ����� 4-7 ͼ��������
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
// ͼ��������
void convolution(cv::Mat src, cv::Mat kernel, cv::Mat& dst)
{
	// ���ͼ����
	dst.create(abs(src.rows - kernel.rows) + 1,
		abs(src.cols - kernel.cols) + 1, src.type());
	cv::Size dftSize;
	// ���㸵��Ҷ�任�ߴ�
	dftSize.width = getOptimalDFTSize(src.cols +
		kernel.cols - 1);
	dftSize.height = getOptimalDFTSize(src.rows +
		kernel.rows - 1);
	// ������ʱͼ���ʼ��Ϊ0
	cv::Mat tempA(dftSize, src.type(), Scalar::all(0));
	cv::Mat tempB(dftSize, kernel.type(), Scalar::all(0));
	// �������򿽱�
	cv::Mat roiA(tempA, Rect(0, 0, src.cols, src.rows));
	src.copyTo(roiA);
	cv::Mat roiB(tempB, Rect(0, 0, kernel.cols, kernel.rows));
	kernel.copyTo(roiB);
	// ����Ҷ�任
	dft(tempA, tempA, 0, src.rows);
	dft(tempB, tempB, 0, kernel.rows);
	// ��������Ƶ��ͼ��ÿһ��Ԫ�صĳ˷�
	mulSpectrums(tempA, tempB, tempA, DFT_COMPLEX_OUTPUT);
	// �任��������з���
	dft(tempA, tempA, DFT_INVERSE + DFT_SCALE, dst.rows);
	// ������������ͼ��
	tempA(Rect(0, 0, dst.cols, dst.rows)).copyTo(dst);
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg", 0);
	if (srcImage.empty())
		return -1;
	// ������������
	cv::Mat kernel = (cv::Mat_<float>(3, 3) << 1, 1, 1,
		1, 1, 1,
		1, 1, 1);
	imshow("srcImage", srcImage);
	srcImage.convertTo(srcImage, CV_32F);
	cv::Mat resultImage;
	// �������
	convolution(srcImage, kernel, resultImage);
	// ��һ��������
	normalize(resultImage, resultImage, 0, 1, CV_MINMAX);
	cv::imshow("resultImage", resultImage);
	cv::waitKey(0);
	return 0;
}
