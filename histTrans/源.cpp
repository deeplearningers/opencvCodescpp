// ���ܣ����� 3-12 ֱ��ͼ�任��������
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
	// ��һ��������ͼ���ֱ��ͼ
	const int channels[1] = { 0 };
	const int histSize[1] = { 256 };
	float hranges[2] = { 0, 255 };
	const float* ranges[1] = { hranges };
	cv::MatND hist;
	calcHist(&srcGray, 1, channels, cv::Mat(),
		hist, 1, histSize, ranges);
	// �ڶ���������Ԥ�����ͳ�ƻҶȼ��任
	int segThreshold = 50;
	// �ɵ͵��߽��в���
	int iLow = 0;
	for (; iLow < histSize[0]; iLow++) {
		if (hist.at<float>(iLow) > segThreshold) {
			break;
		}
	}
	// �ɸߵ��ͽ��в���
	int iHigh = histSize[0] - 1;
	for (; iHigh >= 0; iHigh--) {
		if (hist.at<float>(iHigh) > segThreshold) {
			break;
		}
	}
	// ���������������ұ�
	cv::Mat lookUpTable(cv::Size(1, 256), CV_8U);
	for (int i = 0; i < 256; i++) {
		if (i < iLow){
			lookUpTable.at<uchar>(i) = 0;
		}
		else if (i > iHigh) {
			lookUpTable.at<uchar>(i) = 255;
		}
		else {
			lookUpTable.at<uchar>(i) = static_cast<uchar>(
				255.0 * (i - iLow) / (iHigh - iLow + 0.5));//�任����
		}
	}
	// ���Ĳ���ͨ�����ұ����ӳ��任
	cv::Mat histTransResult;
	cv::LUT(srcGray, lookUpTable, histTransResult);
	// ��ʾͼ��
	cv::imshow("srcGray", srcGray);
	cv::imshow("histTransResult", histTransResult);
	cv::waitKey(0);
	return 0;
}
