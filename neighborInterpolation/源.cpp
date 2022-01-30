// ���ܣ����� 4-1 ����ڲ�ֵʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��//
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
using namespace cv;
using namespace std;
// ʵ������ڲ�ֵͼ������
cv::Mat nNeighbourInterpolation(cv::Mat srcImage)
{
	// �ж�������Ч��
	CV_Assert(srcImage.data != NULL);
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	// ����Ŀ��ͼ��
	cv::Mat dstImage = cv::Mat(
		cv::Size(150, 150), srcImage.type(),
		cv::Scalar::all(0));
	int dstRows = dstImage.rows;
	int dstCols = dstImage.cols;
	// ����ת�� ��ȡ���ű���
	float cx = (float)cols / dstCols;
	float ry = (float)rows / dstRows;
	std::cout << "cx: " << cx << "ry:" << ry << std::endl;
	// ����ͼ��������Ų���
	for (int i = 0; i < dstCols; i++)
	{
		// ȡ����ȡĿ��ͼ����Դͼ���Ӧ����
		int ix = cvFloor(i * cx);
		for (int j = 0; j < dstRows; j++)
		{
			int jy = cvFloor(j * ry);
			// �߽紦�� ��ָֹ��Խ��
			if (ix > cols - 1)
				ix = cols - 1;
			if (jy > rows - 1)
				jy = rows - 1;
			// ӳ�����
			dstImage.at<cv::Vec3b>(j, i) =
				srcImage.at<cv::Vec3b>(jy, ix);
		}
	}
	return  dstImage;
}
int main()
{
	// ͼ��Դ��ȡ����֤
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return -1;
	// ����ڲ�ֵ���Ų���
	cv::Mat dstImage = nNeighbourInterpolation(srcImage);
	cv::imshow("srcImage", srcImage);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
