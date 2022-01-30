// ���ܣ����� 3-13 ֱ��ͼ�任�����ۼ�
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
int main()
{
	// ͼ���ȡ����֤
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return 1;
	// ת��Ϊ�Ҷ�ͼ��
	cv::Mat srcGray;
	cvtColor(srcImage, srcGray, CV_BGR2GRAY);
	// ����ͼ���ֱ��ͼ
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float hranges[2] = { 0, 255 };
	const float* ranges[1] = { hranges };
	cv::Mat hist;
	calcHist(&srcGray, 1, channels, cv::Mat(),
		hist, 1, histSize, ranges);
	float table[256];
	int nPix = srcGray.cols * srcGray.rows;
	// ����ӳ���
	for (int i = 0; i < 256; i++) {
		float temp[256];
		// ���ر任
		temp[i] = hist.at<float>(i) / nPix * 255;
		if (i != 0) {
			// �����ۼ�
			table[i] = table[i - 1] + temp[i];
		}
		else {
			table[i] = temp[i];
		}
	}
	// ͨ��ӳ����б����
	cv::Mat lookUpTable(cv::Size(1, 256), CV_8U);
	for (int i = 0; i < 256; i++) {
		lookUpTable.at<uchar>(i) =
			static_cast<uchar>(table[i]);
	}
	cv::Mat histTransResult;
	cv::LUT(srcGray, lookUpTable, histTransResult);
	// ��ʾͼ��
	cv::imshow("srcGray", srcGray);
	cv::imshow("histTransResult", histTransResult);
	cv::waitKey(0);
	return 0;
}
