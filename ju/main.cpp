#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
Mat src, src_gray, dst;
const char* output_win = "output";
RNG rng(12345);
int threshold_value = 70;
int threshold_max = 255;
void moments_Callback(int, void*);

int main(int argc, char**argv)
{

	src = imread("F:\\processImage\\yuan.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0,BORDER_DEFAULT);

	createTrackbar("threshold:", "input", &threshold_value, threshold_max, moments_Callback);
	moments_Callback(0, 0);

	cvWaitKey(0);
	return 0;
}
void moments_Callback(int, void*){
	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	Canny(src_gray, canny_output, threshold_value, threshold_value * 2, 3, false);
	findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

	vector<Moments> contours_moments(contours.size()); //定义Moments数组
	vector<Point2f> ccs(contours.size());
	for (size_t i = 0; i < contours.size();i++)
	{
		contours_moments[i] = moments(contours[i]);  //小写是函数
		ccs[i] = Point(static_cast<float>(contours_moments[i].m10) / contours_moments[i].m00,
			static_cast<float>(contours_moments[i].m01) / contours_moments[i].m00); //中心位置坐标xy
	} 
	Mat drawImage = Mat::zeros(src.size(), CV_8UC3);
	src.copyTo(drawImage);
	for (size_t j = 0; j < contours.size();j++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		printf("center point  x:%.2f  y:%.2f\n", ccs[j].x, ccs[j].y);
		printf("contours %d  area:%.2f   arc length: %.2f\n",j, contourArea(contours[j]), arcLength(contours[j],true)); //面积和长度
		drawContours(drawImage, contours, j, color, 2, 8, hierachy, 0, Point(-1, -1));
		circle(drawImage, ccs[j], 2, color, 5, 8);
	}
	imshow(output_win, drawImage);
}