#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

#define threshold_diff1 55 //设置简单帧差法阈值
#define threshold_diff2 55 //设置简单帧差法阈值

using namespace cv;
using namespace std;

int main(int argc, unsigned char* argv[])
{
	Mat img_src1, img_src2, img_src3;//3帧法需要3帧图片
	Mat img_dst, gray1, gray2, gray3;
	Mat gray_diff1, gray_diff2;//存储2次相减的图片
	Mat gray_diff11, gray_diff12;
	Mat gray_diff21, gray_diff22;
	Mat gray;//用来显示前景的
	bool pause = false;

	VideoCapture vido_file("20200425000904.avi");//在这里改相应的文件名
												 //capture.get十分强大 可以获得帧的很多信息
	int frame_width = (int)vido_file.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = (int)vido_file.get(CAP_PROP_FRAME_HEIGHT);
	int frame_number = vido_file.get(CAP_PROP_FRAME_COUNT);
	cout << "frame_width is " << frame_width << endl;
	cout << "frame_height is " << frame_height << endl;
	cout << "frame_number is " << frame_number << endl;
	vido_file.set(CAP_PROP_POS_FRAMES, 1);
	vido_file >> img_src1;
	cvtColor(img_src1, gray1, CV_BGR2GRAY);

	vido_file.set(CAP_PROP_POS_FRAMES, frame_number/2);
	vido_file >> img_src2;
	cvtColor(img_src2, gray2, CV_BGR2GRAY);

	vido_file.set(CAP_PROP_POS_FRAMES, frame_number - 1);
	vido_file >> img_src3;
	cvtColor(img_src3, gray3, CV_BGR2GRAY);

	Sobel(gray1, gray1, CV_8U, 1, 0, 3, 0.5, 128);
	Sobel(gray2, gray2, CV_8U, 1, 0, 3, 0.5, 128);
	Sobel(gray3, gray3, CV_8U, 1, 0, 3, 0.5, 128);

	subtract(gray2, gray1, gray_diff11);//第二帧减第一帧
	subtract(gray1, gray2, gray_diff12);
	add(gray_diff11, gray_diff12, gray_diff1);
	subtract(gray3, gray2, gray_diff21);//第三帧减第二帧
	subtract(gray2, gray3, gray_diff22);
	add(gray_diff21, gray_diff22, gray_diff2);

	for (int i = 0; i<gray_diff1.rows; i++)
		for (int j = 0; j<gray_diff1.cols; j++)
		{
			if (abs(gray_diff1.at<unsigned char>(i, j)) >= threshold_diff1)//这里模板参数一定用unsigned char，否则一直报错
				gray_diff1.at<unsigned char>(i, j) = 255;            //第一次相减阈值处理
			else gray_diff1.at<unsigned char>(i, j) = 0;

			if (abs(gray_diff2.at<unsigned char>(i, j)) >= threshold_diff2)//第二次相减阈值处理
				gray_diff2.at<unsigned char>(i, j) = 255;
			else gray_diff2.at<unsigned char>(i, j) = 0;
		}
	bitwise_and(gray_diff1, gray_diff2, gray);
	dilate(gray, gray, Mat());
	erode(gray, gray, Mat());

	namedWindow("1", 1);
	/*imshow("1", gray_diff11);
	waitKey(1000);
	imshow("1", gray_diff12);
	waitKey(1000);
	imshow("1", gray_diff1);
	waitKey(1000);
	imshow("1", gray_diff21);
	waitKey(1000);
	imshow("1", gray_diff22);
	waitKey(1000);
	imshow("1", gray_diff2);*/
	imshow("1", gray);
	//画出目标
	//vector<vector<Point>> v;
	//vector<Vec4i> hierarchy;
	//Mat result;
	//Rect rect;
	//findContours(gray, v, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//for (int i = 0; i < hierarchy.size(); i++)
	//{
	//	rect = boundingRect(v.at(i));
	//	//rect.width *= 1.5;
	//	rect.height *= 1.5;
	//	// 画最小的圆，贴着黑色
	//	//drawContours(currentframe, v, i, Scalar(0, 0, 255), 1, 8, hierarchy);
	//	// 画矩形包围圆
	//	rectangle(img_src1, rect, Scalar(0, 255, 0), 2);
	//}
	//imshow("2", img_src1);
	waitKey(0);

	return 0;
}
