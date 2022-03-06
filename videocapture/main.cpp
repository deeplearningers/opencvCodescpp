//// ���ܣ����� 2-15 VideoCapture ��ȡ�ļ�����
//// ���ߣ���ΰ zhu1988wei@163.com
//// ��Դ����OpenCVͼ������ʵ����
//// ���ͣ�http://blog.csdn.net/zhuwei1988
//// ���£�2016-8-1
//// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//int main()
//{
//	// �������VideoCapture����
//	VideoCapture capture;
//	// ��ȡ��Ƶ�ļ�
//	capture.open("..\\images\\car.avi");
//	//  �ж���Ƶ����ȡ�Ƿ���ȷ
//	if (!capture.isOpened())
//	{
//		std::cout << "fail to open video!" << std::endl;
//		return -1;
//	}
//	// ��ȡ��Ƶ�����Ϣ-֡��
//	long nTotalFrame = capture.get(CV_CAP_PROP_FRAME_COUNT);
//	std::cout << "nTotalFrame = " << nTotalFrame << std::endl;
//	// ��ȡ��Ƶ�����Ϣ-֡���ؿ�� 
//	int  frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
//	int  frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
//	std::cout << "frameHeight = " << frameHeight << std::endl;
//	std::cout << "frameWidth = " << frameWidth << std::endl;
//	// ��ȡ��Ƶ�����Ϣ-֡��
//	double FrameRate = capture.get(CV_CAP_PROP_FPS);
//	std::cout << "FrameRate = " << FrameRate << std::endl;
//	cv::Mat frameImg;
//	// read������ȡ��ʾ֡
//	long nCount = 1;
//	while (true)
//	{
//		std::cout << " Current frame: " << nCount << std::endl;
//		capture >> frameImg;
//		// �жϵ�ǰ��ȡ�ļ�   
//		if (!frameImg.empty())
//		{
//			imshow("frameImg", frameImg);
//		}
//		else
//		{
//			break;
//		}
//		// ���¼�����q���˳�
//		if (char(waitKey(1)) == 'q')
//		{
//			break;
//		}
//		nCount++;
//	}
//	// ��Ƶ�ͷ�
//	capture.release();
//	return 0;
//}


// ���ܣ����� 2-16 ��Ƶд����
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��



#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	// ��Ƶ���������·������
	string sourceVideoPath = "..\\images\\car.avi";
	string outputVideoPath = "..\\images\\testcar.avi";
	// ��Ƶ����
	VideoCapture inputVideo(sourceVideoPath);
	// �����Ƶ�������Ч��      
	if (!inputVideo.isOpened())
	{
		cout << "fail to open!" << endl;
		return -1;
	}
	VideoWriter outputVideo;
	// ��ȡ��Ƶ�ֱ���
	cv::Size videoResolution = cv::Size((int)inputVideo.get(
		CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(
		CV_CAP_PROP_FRAME_HEIGHT));
	double fps = inputVideo.get(CV_CAP_PROP_FPS);
	// ��ȡ��Ƶ֡��
	cout << "totalFrame��" << inputVideo.get(
		CV_CAP_PROP_FRAME_COUNT) << endl;
	// ��ȡ��Ƶ��֡��   
	cout << "fps��" << inputVideo.get(CV_CAP_PROP_FPS) << endl;
	// ��ȡ��Ƶͼ����
	cout << "videoResolution��" << videoResolution.width <<
		" " << videoResolution.height << endl;
	// open����������� 
	outputVideo.open(outputVideoPath, -1, 25.0,
		videoResolution, true);
	if (!outputVideo.isOpened())
	{
		cout << "fail to open!" << endl;
		return -1;
	}
	cv::Mat frameImg;
	int count = 0;
	// vector RGB����
	std::vector< cv::Mat > rgb;
	cv::Mat resultImg;
	for (int i = 0; i < 30; i++)
	{
		inputVideo >> frameImg;
		// ��Ƶ֡�����ж�
		if (!frameImg.empty())
		{
			count++;
			cv::imshow("frameImg", frameImg);
			// �������ͨ��rgb
			cv::split(frameImg, rgb);
			for (int i = 0; i < 3; i++)
			{
				if (i != 0)
				{
					// ��ȡBͨ������
					rgb[i] = cv::Mat::zeros(videoResolution,
						rgb[0].type());
				}
				// ͨ���ϲ�
				cv::merge(rgb, resultImg);
			}
			cv::imshow("resultImg", resultImg);
			outputVideo << resultImg;
		}
		else
		{
			break;
		}
		// ���¼�����q���˳�
		if (char(waitKey(1)) == 'q')
		{
			inputVideo.release();
			outputVideo.release();
			break;
		}
	}
	std::cout << "writeTotalFrame��" << count << std::endl;

	inputVideo.release();
	outputVideo.release();
	return 0;
}
