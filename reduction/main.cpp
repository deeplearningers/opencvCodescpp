// ���ܣ����� 2-10 ͼ�����Ų���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream> 
using namespace cv;
// ���ڵȼ����ȡͼ������
cv::Mat imageReduction1(cv::Mat &srcImage, float kx, float ky)
{
	// ��ȡ���ͼ��ֱ���
	int nRows = cvRound(srcImage.rows * kx);
	int nCols = cvRound(srcImage.cols * ky);
	cv::Mat resultImage(nRows, nCols, srcImage.type());
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			// ����ˮƽ���Ӽ�������
			int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
			// ���ݴ�ֱ���Ӽ�������
			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
			resultImage.at<cv::Vec3b>(i, j) =
				srcImage.at<cv::Vec3b>(x, y);
		}
	}
	return resultImage;
}
cv::Vec3b areaAverage(const cv::Mat &srcImage,
	Point_<int> leftPoint, Point_<int> rightPoint)
{
	int temp1 = 0, temp2 = 0, temp3 = 0;
	// ���������ӿ����ص����
	int nPix = (rightPoint.x - leftPoint.x + 1)*
		(rightPoint.y - leftPoint.y + 1);
	// �����ӿ����ͨ��������ֵ���
	for (int i = leftPoint.x; i <= rightPoint.x; i++){
		for (int j = leftPoint.y; j <= rightPoint.y; j++){
			temp1 += srcImage.at<cv::Vec3b>(i, j)[0];
			temp2 += srcImage.at<cv::Vec3b>(i, j)[1];
			temp3 += srcImage.at<cv::Vec3b>(i, j)[2];
		}
	}
	// ��ÿ��ͨ�����ֵ
	Vec3b vecTemp;
	vecTemp[0] = temp1 / nPix;
	vecTemp[1] = temp2 / nPix;
	vecTemp[2] = temp3 / nPix;
	return vecTemp;
}
cv::Mat  imageReduction2(const Mat &srcImage, double kx,
	double ky)
{
	// ��ȡ���ͼ��ֱ���
	int nRows = cvRound(srcImage.rows * kx);
	int nCols = cvRound(srcImage.cols * ky);
	cv::Mat resultImage(nRows, nCols, srcImage.type());
	// �����ӿ�����Ͻ���������
	int leftRowCoordinate = 0;
	int leftColCoordinate = 0;
	for (int i = 0; i < nRows; ++i)
	{
		// ����ˮƽ���Ӽ�������
		int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
		for (int j = 0; j < nCols; ++j) {
			// ���ݴ�ֱ���Ӽ�������
			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
			// ��������ӿ�ľ�ֵ       
			resultImage.at<Vec3b>(i, j) =
				areaAverage(srcImage,
				Point_<int>(leftRowCoordinate,
				leftColCoordinate), Point_<int>(x, y));
			// �������ӿ����Ͻǵ������꣬�����겻��
			leftColCoordinate = y + 1;
		}
		leftColCoordinate = 0;
		// �������ӿ����Ͻǵ�������
		leftRowCoordinate = x + 1;
	}
	return resultImage;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	cv::Mat resultImage1 =
		imageReduction1(srcImage, 0.5, 0.5);
	cv::imshow("res1", resultImage1);
	cv::Mat resultImage2 =
		imageReduction2(srcImage, 0.5, 0.5);
	cv::imshow("res2", resultImage2);
	cv::waitKey(0);
	return 0;
}
