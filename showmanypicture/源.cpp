// ���ܣ����� 2-30 ��������ʾ���ͼ��
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
void showManyImages(const std::vector<cv::Mat> &srcImages,
	cv::Size imgSize)
{
	int nNumImages = srcImages.size();
	cv::Size nSizeWindows;
	if (nNumImages > 12)
	{
		std::cout << " Not more than 12 images!" << std::endl;
		return;
	}
	// ����ͼƬ����������ȷ���ָ�С������̬
	switch (nNumImages)
	{
	case 1: nSizeWindows = cv::Size(1, 1); break;
	case 2: nSizeWindows = cv::Size(2, 1); break;
	case 3:
	case 4: nSizeWindows = cv::Size(2, 2); break;
	case 5:
	case 6: nSizeWindows = cv::Size(3, 2); break;
	case 7:
	case 8: nSizeWindows = cv::Size(4, 2); break;
	case 9: nSizeWindows = cv::Size(3, 3); break;
	default:nSizeWindows = cv::Size(4, 3); break;
	}
	// ����Сͼ��ߴ磬��϶���߽�
	int nShowImageSize = 200;
	int nSplitLineSize = 15;
	int nAroundLineSize = 50;
	// �������ͼ��ͼ���С��������Դȷ��
	const int imagesHeight = nShowImageSize * nSizeWindows.width +
		nAroundLineSize + (nSizeWindows.width - 1) *
		nSplitLineSize;
	const int imagesWidth = nShowImageSize*nSizeWindows.height +
		nAroundLineSize + (nSizeWindows.height - 1) *
		nSplitLineSize;
	std::cout << imagesWidth << " " << imagesHeight << std::endl;
	cv::Mat showWindowImages(imagesWidth, imagesHeight,
		CV_8UC3, cv::Scalar(0, 0, 0));
	// ��ȡ��ӦСͼ������Ͻ�����X��Y
	int posX = (showWindowImages.cols - (nShowImageSize*
		nSizeWindows.width + (nSizeWindows.width - 1)*
		nSplitLineSize)) / 2;
	int posY = (showWindowImages.rows - (nShowImageSize*
		nSizeWindows.height + (nSizeWindows.height - 1)*
		nSplitLineSize)) / 2;
	std::cout << posX << " " << posY << std::endl;
	int tempPosX = posX;
	int tempPosY = posY;
	// ��ÿһС��ͼ�����ϴ�ͼ��
	for (int i = 0; i < nNumImages; i++)
	{
		// Сͼ������ת��
		if ((i % nSizeWindows.width == 0) && (tempPosX != posX))
		{
			tempPosX = posX;
			tempPosY += (nSplitLineSize + nShowImageSize);
		}
		// ����Rect����Сͼ�����ڴ�ͼ����Ӧ����
		cv::Mat tempImage = showWindowImages(cv::Rect(tempPosX,
			tempPosY, nShowImageSize, nShowImageSize));
		// ����resize����ʵ��ͼ������
		resize(srcImages[i], tempImage,
			cv::Size(nShowImageSize, nShowImageSize));
		tempPosX += (nSplitLineSize + nShowImageSize);
	}
	cv::imshow("showWindowImages", showWindowImages);
}
int main()
{
	// ͼ��Դ����
	std::vector<cv::Mat> srcImages(9);
	srcImages[0] = cv::imread("..\\images\\flower.jpg");
	srcImages[1] = cv::imread("..\\images\\flower.jpg");
	srcImages[2] = cv::imread("..\\images\\flower.jpg");
	srcImages[3] = cv::imread("..\\images\\flower2.jpg");
	srcImages[4] = cv::imread("..\\images\\flower2.jpg");
	srcImages[5] = cv::imread("..\\images\\flower2.jpg");
	srcImages[6] = cv::imread("..\\images\\flower3.jpg");
	srcImages[7] = cv::imread("..\\images\\flower3.jpg");
	srcImages[8] = cv::imread("..\\images\\flower3.jpg");
	// �жϵ�ǰvector�������ȷ��
	for (int i = 0; i < srcImages.size(); i++)
	{
		if (!srcImages[i].data)
		{
			std::cout << "read error!" << std::endl;
			return -1;
		}
	}
	// ���õ�������ʾͼ��
	showManyImages(srcImages, cv::Size(512, 400));
	cv::waitKey(0);
	return 0;
}
