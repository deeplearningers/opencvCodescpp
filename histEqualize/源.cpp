// ���ܣ����� 3-10 �Ҷ�ֱ��ͼ���⻯ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/opencv.hpp>
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return 1;
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	cv::imshow("srcGray", srcGray);
	// ֱ��ͼ���⻯
	cv::Mat heqResult;
	cv::equalizeHist(srcGray, heqResult);
	cv::imshow("heqResult", heqResult);
	cv::waitKey(0);
	return 0;
}
