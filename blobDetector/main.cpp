// ���ܣ����� 7-7 ����������
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��//
#include "opencv2/opencv.hpp"  
#include <iostream>
using namespace cv;
int main()
{
	cv::Mat srcImage =
		cv::imread("..\\images\\boudingRect.jpg");
	if (!srcImage.data)
		return -1;
	cv::imshow("srcImage", srcImage);
	// �����ؼ���
	std::vector<KeyPoint> keypoints;
	//  blob�ඨ��
	SimpleBlobDetector::Params params;
	// ��������
	params.filterByArea = true;
	params.minArea = 15;
	params.maxArea = 50;
	params.filterByColor = true;
	params.blobColor = 0;	
	Ptr<SimpleBlobDetector>	blobDetector = SimpleBlobDetector::create(params);
	// ����������
	blobDetector->detect(srcImage, keypoints);
	// ���ƹؼ���
	drawKeypoints(srcImage, keypoints,
		srcImage, Scalar(255, 0, 0));
	cv::imshow("result", srcImage);
	cv::waitKey();
	return 0;
}
