// ���ܣ����� 2-28 LUT ���ɫ����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
int main()
{
	// Դͼ�����뼰�ж�
	cv::Mat srcImage = cv::imread("..\\images\\flower4.jpg");
	if (!srcImage.data)
		return 1;
	// ת��Ϊ�Ҷ�ͼ��
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);

	cv::namedWindow("srcImage");
	cv::imshow("srcImage", srcGray);

	int row = srcGray.rows;
	int col = srcGray.cols;
	cv::Mat tempImage = srcGray.clone();
	// ����LUT ��ɫtable
	uchar LutTable[256];
	for (int i = 0; i < 256; ++i)
		LutTable[i] = 255 - i;
	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* pData = lookUpTable.data;
	// ����ӳ���
	for (int i = 0; i < 256; ++i)
		pData[i] = LutTable[i];
	// Ӧ����������в���
	cv::LUT(srcGray, lookUpTable, tempImage);

	cv::namedWindow("dyn_threshold");
	cv::imshow("dyn_threshold", tempImage);
	cv::waitKey(0);
	return 0;
}
