// ���ܣ����� 5-17 LSD �����߼��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <iostream>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
int main()
{

	cv::Mat srcImage =
		cv::imread("..\\images\\building.jpg", 0);
	if (!srcImage.data)
		return -1;
	GaussianBlur(srcImage, srcImage, cv::Size(3, 3), 0.5, 0.5, 4);
	// canny��Ե���
	Canny(srcImage, srcImage, 65, 300, 3);
	// ����LSD�����
#if 1
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
#else
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_NONE);
#endif
	double start = double(getTickCount());
	vector<Vec4f> lines_std;
	// �߼��
	ls->detect(srcImage, lines_std);
	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();
	std::cout << "It took " << duration_ms << " ms." << std::endl;
	// ��ͼ�߼����
	//cv::Mat drawnLines = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC1);
	Mat drawnLines(srcImage);
	ls->drawSegments(drawnLines, lines_std);
	cv::imshow("Standard refinement", drawnLines);
	cv::waitKey();
	return 0;
}
