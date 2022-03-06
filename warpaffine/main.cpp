// ���ܣ����� 2-14 ͼ�����任
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream> 
using namespace cv;
int main()
{
	// ��ȡͼ����֤������ȷ
	cv::Mat srcImage = cv::imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;
	//�������任�Ķ�ά������
	//Դͼ���Ŀ��ͼ���Ӧӳ�������
	cv::Point2f srcPoint[3];
	cv::Point2f resPoint[3];
	srcPoint[0] = cv::Point2f(0, 0);
	srcPoint[1] = cv::Point2f(nCols - 1, 0);
	srcPoint[2] = cv::Point2f(0, nRows - 1);
	resPoint[0] = cv::Point2f(nCols * 0, nRows*0.33);
	resPoint[1] = cv::Point2f(nCols*0.85, nRows*0.25);
	resPoint[2] = cv::Point2f(nCols*0.15, nRows*0.7);
	// �������任����2X3
	cv::Mat warpMat(cv::Size(2, 3), CV_32F);
	cv::Mat resultImage =
		cv::Mat::zeros(nRows, nCols, srcImage.type());
	// �������任���󣬼�����任��2*3����
	warpMat = cv::getAffineTransform(srcPoint, resPoint);
	// ���ݷ���������ͼ�����任
	cv::warpAffine(srcImage, resultImage,
		warpMat, resultImage.size());
	cv::imshow("resultImage1", resultImage);
	// ����任��������
	cv::Point2f centerPoint = cv::Point2f(nCols / 2, nRows / 2);
	double angle = -50;
	double scale = 0.7;
	// ��ȡ����任����
	warpMat = getRotationMatrix2D(centerPoint, angle, scale);
	// ��ԭͼ��Ƕȷ���任
	cv::warpAffine(srcImage, resultImage,
		warpMat, resultImage.size());
	cv::imshow("resultImage2", resultImage);
	cv::waitKey(0);
}
