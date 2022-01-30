#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	const char* filename = "timg.jpg";

	Mat img = imread(filename);
	if (img.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}
	Mat img3, img2;
	//�Ѳ�ɫͼת��Ϊ�ڰ�ͼ��
	cvtColor(img, img2, COLOR_BGR2GRAY);   
	GaussianBlur(img2, img2, Size(3, 3),2, 2);
	threshold(img2, img3, 210, 255, THRESH_BINARY);
	adaptiveThreshold(img3, img3, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 10);
	//// ��̬ѧ����
	//Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));   // ������̬ѧ�����ĽṹԪ
	//morphologyEx(img3, img3, MORPH_CLOSE, kernel, Point(-1, -1));      //�ղ���

	//kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));     // ������̬ѧ�����ĽṹԪ
	//morphologyEx(img3, img3, MORPH_OPEN, kernel, Point(-1, -1));                 //������
	// Ѱ������
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	findContours(img3, contours, hireachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());

	Mat result_img = Mat::zeros(img.size(), CV_8UC3);     // ������ԭͼͬ��С�ĺ�ɫ����
	Point circle_center;              //����Բ������
	for (auto t = 0; t < contours.size(); ++t)
	{
		// �������
		double area = contourArea(contours[t]);     //����㼯��Χ��������
		if (area < 50 && contours.at(t).size()<10)            //ɹѡ�������������100������
			continue;
		// ���ݱȹ���
		Rect rect = boundingRect(contours[t]);            // ��㼯����Сֱ���������
		float ratio = float(rect.width) / float(rect.height);        //�����߱�

		if (ratio < 1.1 && ratio > 0.9)       //��ΪԲ�����ֱ�����ο϶�������һ�������Σ���˿�߱Ƚӽ�1.0
		{
			drawContours(result_img, contours, t, Scalar(0, 100, 100), -1, 8, Mat(), 0, Point());    ////�ں�ɫ����ͼ�ϻ���Բ��ע�����в���-1������
			printf("Բ�����: %f\n", area);
			double arc_length = arcLength(contours[t], true);         //����㼯��Χ������ܳ�
			printf("Բ���ܳ� : %f\n", arc_length);
			int x = rect.x + rect.width / 2;
			int y = rect.y + rect.height / 2;
			circle_center = Point(x, y);          //�õ�Բ������
			cout << "Բ�����꣺" << "��" << circle_center.x << " " << "��" << circle_center.y << endl;
			circle(result_img, circle_center, 2, Scalar(0, 255, 255), 2, 8, 0);
		}
	}
	waitKey();
	return 0;
}