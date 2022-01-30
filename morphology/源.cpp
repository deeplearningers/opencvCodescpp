//// ���ܣ����� 6-2 ��̬ѧ���ղ���
//// ���ߣ���ΰ zhu1988wei@163.com
//// ��Դ����OpenCVͼ������ʵ����
//// ���ͣ�http://blog.csdn.net/zhuwei1988
//// ���£�2016-8-1
//// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//int main()
//{
//	cv::Mat srcImage = cv::imread("..\\images\\test.jpg");
//	if (!srcImage.data)
//		return 1;
//	cv::Mat srcGray, segImage;
//	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//	// ��ֵ��
//	cv::threshold(srcGray, segImage,
//		255 * (0.5), 255, cv::THRESH_BINARY);
//	// ����ṹԪ��
//	cv::Mat element = cv::getStructuringElement(
//		cv::MORPH_ELLIPSE, cv::Size(20, 20));
//	// ��̬ѧ�ղ���
//	cv::Mat closedMat;
//	cv::morphologyEx(segImage, closedMat,
//		cv::MORPH_CLOSE, element);
//	// ��̬ѧ������ 
//	cv::Mat openedMat;
//	cv::morphologyEx(segImage, openedMat,
//		cv::MORPH_OPEN, element);
//	cv::imshow(" srcGray ", srcGray);
//	cv::imshow(" segImage ", segImage);
//	cv::imshow(" closedMat ", closedMat);
//	cv::imshow(" openedMat ", openedMat);
//	cv::waitKey();
//	return 0;
//}
// ���ܣ����� 6-3 ��̬ѧ�ݶȲ���
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//int main()
//{
//	cv::Mat srcImage = cv::imread("..\\images\\test.jpg");
//	if (!srcImage.data)
//		return 1;
//	cv::Mat srcGray;
//	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//	// ����ṹԪ��
//	cv::Mat element = cv::getStructuringElement(
//		cv::MORPH_RECT, cv::Size(9, 9));
//	cv::Mat gradMat;
//	// ��̬ѧ�ݶ�
//	cv::morphologyEx(srcGray, gradMat,
//		cv::MORPH_GRADIENT, element);
//	cv::imshow(" srcGray ", srcGray);
//	cv::imshow(" gradMat ", gradMat);
//	cv::waitKey();
//	return 0;
//}

// ���ܣ�����  6-4 ��̬ѧTop-Hat ����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower4.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	// ����ṹԪ��
	cv::Mat element = cv::getStructuringElement(
		cv::MORPH_RECT, cv::Size(15, 15));
	cv::Mat topHatMat, blackHatMat;
	// ��̬ѧTop-Hat ��ñ
	cv::morphologyEx(srcGray, topHatMat,
		cv::MORPH_TOPHAT, element);
	// ��̬ѧTop-Hat ��ñ
	cv::morphologyEx(srcGray, blackHatMat,
		cv::MORPH_BLACKHAT, element);
	cv::imshow(" srcGray ", srcGray);
	cv::imshow(" topHatMat  ", topHatMat);
	cv::imshow(" blackHatMat ", blackHatMat);
	cv::waitKey();
	return 0;
}

