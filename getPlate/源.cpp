// ���ܣ����� 6-6 ����������ȡ
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
cv::Mat getPlate(int width, int height, cv::Mat srcGray)
{
	cv::Mat result;
	// ��̬ѧ�ݶȼ���Ե
	morphologyEx(srcGray, result, MORPH_GRADIENT,
		Mat(1, 2, CV_8U, Scalar(1)));
	cv::imshow("1result", result);
	// ��ֵ��
	threshold(result, result, 255 * (0.1), 255,
		THRESH_BINARY);
	cv::imshow("2result", result);
	// ˮƽ���������
	if (width >= 400 && width < 600)
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(1, 25, CV_8U, Scalar(1)));
	else if (width >= 200 && width < 300)
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(1, 20, CV_8U, Scalar(1)));
	else if (width >= 600)
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(1, 28, CV_8U, Scalar(1)));
	else
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(1, 15, CV_8U, Scalar(1)));
	// ��ֱ���������
	if (height >= 400 && height < 600)
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(8, 1, CV_8U, Scalar(1)));
	else if (height >= 200 && height < 300)
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(6, 1, CV_8U, Scalar(1)));
	else if (height >= 600)
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(10, 1, CV_8U, Scalar(1)));
	else
		morphologyEx(result, result, MORPH_CLOSE,
		Mat(4, 1, CV_8U, Scalar(1)));
	return result;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\car.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);
	cv::imshow("srcGray", srcGray);
	cv::Mat result = getPlate(400, 300, srcGray);
	// ��ͨ����
	std::vector<std::vector<cv::Point> > blue_contours;
	std::vector<cv::Rect> blue_rect;
	cv::findContours(result.clone(),
		blue_contours, CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	// ��ͨ����� ����Ŀ����ȡ
	for (size_t i = 0; i != blue_contours.size(); ++i)
	{
		cv::Rect rect = cv::boundingRect(blue_contours[i]);
		double wh_ratio = double(rect.width) / rect.height;
		int sub = cv::countNonZero(result(rect));
		double ratio = double(sub) / rect.area();
		if (wh_ratio > 2 && wh_ratio < 8 && rect.height >
			12 && rect.width > 60 && ratio > 0.4)
		{
			//blue_rect.push_back(rect);
			cv::imshow("rect", srcGray(rect));
			cv::waitKey(0);
		}
	}
	cv::imshow("result", result);
	cv::waitKey(0);
	return 0;
}

