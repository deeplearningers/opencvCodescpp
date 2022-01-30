// ���ܣ����� 2-18 ����¼�ʾ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
// ȫ�ֱ��� 
cv::Mat srcImage;
void MouseEvent(int event, int x, int y, int flags, void* data)
{
	char charText[30];
	cv::Mat tempImage, hsvImage;
	tempImage = srcImage.clone();
	// ��������ƶ���ʾRGB��Ϣ
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cv::Vec3b p = tempImage.at<cv::Vec3b>(y, x);
		sprintf(charText, "R=%d, G=%d, B=%d", p[2], p[1], p[0]);
		// дRGB�ı���Ϣ��ͼ��
		cv::putText(tempImage, charText, cv::Point(8, 20),
			cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255, 255, 255));
		imwrite("..\\images\\RGBFlower4.jpg", tempImage);
	}
	// �Ҽ������ƶ���ʾHSV��Ϣ
	else if (event == CV_EVENT_RBUTTONDOWN)
	{
		// ת����HSVͼ��
		cv::cvtColor(tempImage, hsvImage, CV_BGR2HSV);
		cv::Vec3b p = hsvImage.at<cv::Vec3b>(y, x);
		// ��ȡ��Ӧ��ͨ��ֵ
		sprintf(charText, "H=%d, S=%d, V=%d", p[0], p[1], p[2]);
		// дHSV�ı���Ϣ��ͼ��
		cv::putText(tempImage, charText, cv::Point(8, 20),
			cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255, 255, 255));
		imwrite("..\\images\\HSVFlower4.jpg", tempImage);
	}
	// û�а��¼���ʾ��Ӧ����
	else
	{
		// �ƶ������ʾ����
		sprintf(charText, "x=%d, y=%d", x, y);
		// дXY�����ı���Ϣ��ͼ��
		cv::putText(tempImage, charText, cv::Point(8, 20),
			cv::FONT_HERSHEY_PLAIN, 2, CV_RGB(255, 255, 255));
		imwrite("..\\images\\NOFlower4.jpg", tempImage);
	}
	cv::imshow("srcImage", tempImage);

}
int main(int argc, char** argv)
{
	// ��ȡͼ���ж��Ƿ���ȷ����
	srcImage = cv::imread("..\\images\\flower4.jpg");
	if (srcImage.empty())
		return -1;
	// �ص��¼���Ӧ
	cv::namedWindow("srcImage");
	cv::setMouseCallback("srcImage", MouseEvent, 0);
	cv::imshow("srcImage", srcImage);
	cv::waitKey(0);
	return 0;
}
