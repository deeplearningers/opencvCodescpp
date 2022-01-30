// ���ܣ����� 9-4 HDR ͼ������
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
void loadExposureSeq(String path, vector<Mat>& images, vector<float>& times)
{
	// ��ȡ��ǰ·��
	path = path + std::string("\\");
	// ��ȡͼ������ع���Ϣ
	ifstream list_file((path + "list.txt").c_str());
	string name;
	float val;
	//  �������ͼ��Դ��Ϣ����
	while (list_file >> name >> val) {
		Mat img = imread(path + name);
		images.push_back(img);
		times.push_back(1 / val);
	}
	list_file.close();
}
int main(int, char**argv)
{
	vector<Mat> images;
	vector<float> times;
	// ��ȡͼ������
	string strPath = "..\\images\\HDR";
	loadExposureSeq(strPath, images, times);
	// ����Calibrate����
	Mat response;
	Ptr<CalibrateDebevec> calibrate = createCalibrateDebevec();
	// ���������Ӧ��У׼�㷨��������CRF����256����ֵ
	calibrate->process(images, response, times);
	// ����HDRͼ��
	Mat hdr;
	Ptr<MergeDebevec> merge_debevec = createMergeDebevec();
	merge_debevec->process(images, hdr, times, response);
	// ͼ��ӳ�� ����˫���˲� Gamma�任
	Mat ldr;
	Ptr<TonemapDurand> tonemap = createTonemapDurand(2.2f);
	tonemap->process(hdr, ldr);
	// ִ���ع��ں�
	Mat fusion;
	Ptr<MergeMertens> merge_mertens = createMergeMertens();
	merge_mertens->process(images, fusion);
	cv::imshow("hdr", hdr);
	// ������
	imwrite("fusion.png", fusion * 255);
	imwrite("ldr.png", ldr * 255);
	imwrite("hdr.hdr", hdr );
	cv::waitKey(0);
	return 0;
}

