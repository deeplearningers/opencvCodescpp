// ���ܣ����� 2-20 Rect ѡ�����Ȥ����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
// ȫ�ֱ���Դͼ��
cv::Mat srcImage;
// ����1 ����Rectѡ������(100, 180, 150, 50)
void regionExtraction(int xRoi, int yRoi,
	int widthRoi, int heightRoi)
{
	// ָ������������ȡ
	cv::Mat roiImage(srcImage.rows, srcImage.cols, CV_8UC3);
	std::cout << srcImage.rows << " " <<
		srcImage.cols << std::endl;
	// ����Ȥ���򿽱���Ŀ��ͼ��
	srcImage(cv::Rect(xRoi, yRoi, widthRoi,
		heightRoi)).copyTo(roiImage);
	cv::imshow("roiImage", roiImage);
	cv::waitKey(0);
}
int main()
{
	// Դͼ�����뼰�ж�
	srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return 1;
	cv::imshow("ROIing", srcImage);
	//cv::waitKey(0);
	// ����1 ����Rectѡ������(100, 180, 150, 50)
	int xRoi = 80;
	int yRoi = 180;
	int widthRoi = 150;
	int heightRoi = 100;
	regionExtraction(xRoi, yRoi, widthRoi, heightRoi);
	return 0;
}
