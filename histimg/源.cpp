// ���ܣ����� 3-6 �Ҷ�ֱ��ͼ��ʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2\opencv.hpp>  
int main()
{
	// ͼ��Դ��ȡ���ж� 
	cv::Mat Image, ImageGray;
	Image = cv::imread("..\\images\\flower3.jpg");
	if (Image.empty())
		return -1;
	cv::imshow("Image", Image);
	// ת��Ϊ�Ҷ�ͼ��
	cv::cvtColor(Image, ImageGray, CV_BGR2GRAY);
	// ����ֱ��ͼ����
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float pranges[2] = { 0, 255 };
	const float* ranges[1] = { pranges };
	cv::MatND hist;
	// ����ֱ��ͼ
	cv::calcHist(&ImageGray, 1, channels, cv::Mat(), hist, 1,
		histSize, ranges);
	// ��ʼ����������
	int hist_w = 500;
	int hist_h = 500;
	int nHistSize = 255;
	// ����
	int bin_w = cvRound((double)hist_w / nHistSize);
	cv::Mat histImage(hist_w, hist_h,
		CV_8UC3, cv::Scalar(0, 0, 0));
	// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]
	normalize(hist, hist, 0, histImage.rows,
		cv::NORM_MINMAX, -1, cv::Mat());
	// ��ֱ��ͼ�����ϻ���ֱ��ͼ
	for (int i = 1; i < nHistSize; i++)
	{
		line(histImage, cv::Point(bin_w*(i - 1),
			hist_h - cvRound(hist.at<float>(i - 1))),
			cv::Point(bin_w*(i),
			hist_h - cvRound(hist.at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);
	}
	// ��ʾֱ��ͼ
	cv::imshow("histImage", histImage);
	cv::waitKey();
	return 0;
}
