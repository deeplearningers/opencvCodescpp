// ���ܣ����� 3-9 �Զ���ֱ��ͼʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/opencv.hpp>
int main()
{
	// ͼ���ȡ���ж�
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return 1;
	cv::imshow("srcImage", srcImage);
	// �Ҷ�ת��  
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	// ��ʼ��ֱ��ͼ�������
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	// �趨����[0 60],[61 120],[121 160],[161 220],[221 255]
	float hranges[6] = { 0, 60, 120, 160, 220, 255 };
	const float* ranges[1] = { hranges };
	cv::Mat hist;
	// ����ֱ��ͼ
	cv::calcHist(&srcGray, 1,
		channels, cv::Mat(),
		hist, 1, histSize,
		ranges);
	// ��ֱ��ͼ�����ֵ
	double maxHist = 0;
	cv::minMaxLoc(hist, 0, &maxHist, 0, 0);
	// ����ֱ��ͼ��ͼ����
	int hist_Size = hist.rows;
	cv::Mat histImg(hist_Size, hist_Size,
		CV_8U, cv::Scalar(255));
	// ֱ��ͼ����
	for (int h = 0; h < hist_Size; h++)
	{
		float binVal = hist.at<float>(h);
		//��һ�� �������ֵ����任��Χ 
		int intensity = static_cast<int>(binVal *
			hist_Size / maxHist);
		// ��ͼֱ��ͼ��Ϣ
		cv::line(histImg, cv::Point(h, hist_Size),
			cv::Point(h, hist_Size - intensity),
			cv::Scalar::all(0));
	}
	cv::imshow("histImg", histImg);
	cv::waitKey(0);
	return 0;
}
