// ���ܣ����� 5-25 moravec �ǵ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
// MoravecCorners�ǵ���
cv::Mat MoravecCorners(cv::Mat srcImage, int kSize, int threshold)
{
	cv::Mat resMorMat = srcImage.clone();
	// ��ȡ��ʼ��������Ϣ
	int r = kSize / 2;
	const int nRows = srcImage.rows;
	const int nCols = srcImage.cols;
	int nConut = 0;
	CvPoint *pPoint = new CvPoint[nRows*nCols];
	// ͼ�����
	for (int i = r; i < srcImage.rows - r; i++)
	{
		for (int j = r; j < srcImage.cols - r; j++)
		{
			int wV1, wV2, wV3, wV4;
			wV1 = wV2 = wV3 = wV4 = 0;
			// ����ˮƽ��������Ȥֵ
			for (int k = -r; k < r; k++)
				wV1 += (srcImage.at<uchar>(i, j + k) -
				srcImage.at<uchar>(i, j + k + 1))*(srcImage.at
				<uchar>(i, j + k) - srcImage.at<uchar>(i, j + k + 1));
			// ���㴹ֱ��������Ȥֵ
			for (int k = -r; k < r; k++)
				wV2 += (srcImage.at<uchar>(i + k, j) -
				srcImage.at<uchar>(i + k + 1, j))*(srcImage.at
				<uchar>(i + k, j) - srcImage.at<uchar>(i + k + 1, j));
			// ����45�ȷ�������Ȥֵ
			for (int k = -r; k < r; k++)
				wV3 += (srcImage.at<uchar>(i + k, j + k) -
				srcImage.at<uchar>(i + k + 1, j + k + 1))*(srcImage.at
				<uchar>(i + k, j + k) - srcImage.at<uchar>(i + k + 1, j + k + 1));
			// ����135�ȷ�������Ȥֵ
			for (int k = -r; k < r; k++)
				wV4 += (srcImage.at<uchar>(i + k, j - k) -
				srcImage.at<uchar>(i + k + 1, j - k - 1))*(srcImage.at
				<uchar>(i + k, j - k) - srcImage.at<uchar>(i + k + 1, j - k - 1));
			//std::cout << wV1 << wV2 <<  wV3 << wV4 << std::endl;
			// ȡ���е���Сֵ��Ϊ�����ص��������Ȥֵ
			int value = min(min(wV1, wV2), min(wV3, wV4));
			// ����Ȥֵ������ֵ���򽫵��������������� 
			if (value > threshold)
			{
				pPoint[nConut] = cvPoint(j, i);
				nConut++;
			}
		}
	}
	//������Ȥ��
	for (int i = 0; i < nConut; i++)
		cv::circle(resMorMat, pPoint[i], 4, cv::Scalar(255, 255, 0));
	return resMorMat;
}

int main()
{
	cv::Mat srcImage = imread("..\\images\\building.jpg", 0);
	if (!srcImage.data)
		return -1;
	cv::Mat resMorMat = MoravecCorners(srcImage, 5, 10000);
	cv::imshow("srcImage", srcImage);
	cv::imshow("resMorMat", resMorMat);
	cv::waitKey(0);
	return 0;
}