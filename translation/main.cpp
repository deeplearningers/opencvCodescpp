// ���ܣ����� 2-9 ͼ��ƽ�Ʋ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
// ƽ�Ʋ��� ͼ���С����
cv::Mat imageTranslation1(cv::Mat & srcImage, int xOffset,
	int yOffset)
{
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;
	cv::Mat resultImage(srcImage.size(),
		srcImage.type());
	// ����ͼ��
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			// ӳ��任
			int x = j - xOffset;
			int y = i - yOffset;
			// �߽��ж�
			if (x >= 0 && y >= 0 && x < nCols && y < nRows)
				resultImage.at<cv::Vec3b>(i, j) =
				srcImage.ptr<cv::Vec3b>(y)[x];
		}
	}
	return resultImage;
}
// ƽ�Ʋ��� ͼ���С�ı� 
cv::Mat imageTranslation2(cv::Mat & srcImage, int xOffset,
	int yOffset)
{
	// ����ƽ�Ƴߴ�
	int nRows = srcImage.rows + abs(yOffset);
	int nCols = srcImage.cols + abs(xOffset);
	cv::Mat resultImage(nRows, nCols,
		srcImage.type());
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			// ӳ��任
			int x = j - xOffset;
			int y = i - yOffset;
			// �߽��ж�
			if (x >= 0 && y >= 0 && x < nCols && y < nRows)
				resultImage.at<cv::Vec3b>(i, j) =
				srcImage.ptr<cv::Vec3b>(y)[x];
		}
	}
	return resultImage;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\lakeWater.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	int xOffset = 50, yOffset = 80;
	// ͼ����ƽ�Ʋ��ı��С
	cv::Mat resultImage1 =
		imageTranslation1(srcImage, xOffset, yOffset);
	cv::imshow("resultImage1", resultImage1);
	// ͼ����ƽ�Ƹı��С
	cv::Mat resultImage2 =
		imageTranslation2(srcImage, xOffset, yOffset);
	cv::imshow("resultImage2", resultImage2);
	// ͼ����ƽ�Ʋ��ı��С
	xOffset = -50, yOffset = -80;
	cv::Mat resultImage3 =
		imageTranslation1(srcImage, xOffset, yOffset);
	cv::imshow("resultImage3", resultImage3);
	cv::waitKey(0);
	return 0;
}
