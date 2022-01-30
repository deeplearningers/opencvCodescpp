#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
Mat src, src_gray, dst;
const char* output_win = "output";
RNG rng(12345);
int threshold_value = 170;
int threshold_max = 255;
void threshold_callback(int, void*);

int main(int argc, char**argv)
{

	src = imread("F:\\processImage\\qiqiu.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);

	createTrackbar("threshold:", "input", &threshold_value, threshold_max, threshold_callback);
	threshold_callback(0, 0);

	cvWaitKey(0);
	return 0;
}
void threshold_callback(int, void*){
	Mat binary_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	threshold(src_gray, binary_output, threshold_value, threshold_max, THRESH_BINARY);
	//imshow("binary_output", binary_output);
	findContours(binary_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));
	
	vector<vector<Point>> contours_ploy(contours.size());
	vector<Rect> ploy_rects(contours.size()); //最小矩形
	vector<Point2f> ccs(contours.size());    //最小圆
	vector<float> radius(contours.size());

	vector<RotatedRect> minRects(contours.size());
	vector<RotatedRect> myellipse(contours.size());

	for (size_t i = 0; i < contours.size();i++)
	{
		approxPolyDP(contours[i], contours_ploy[i], 3,true); //拟合轮廓的多边形
		ploy_rects[i] = boundingRect(contours_ploy[i]);
		minEnclosingCircle(contours_ploy[i], ccs[i], radius[i]);
		if (contours_ploy[i].size()>5)
		{
			myellipse[i] = fitEllipse(contours_ploy[i]);
			minRects[i] = minAreaRect(contours_ploy[i]);
		}
		
		//绘制矩形和圆
		src.copyTo(dst);
		Point2f pts[4];
		for (size_t j = 0; j < contours.size();j++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			//rectangle(dst, ploy_rects[j], color, 2, 8, 0);
			//circle(dst, ccs[j], radius[j], color, 2, 8, 0);
			if(contours_ploy[j].size()>5)
			{
				ellipse(dst, myellipse[j], color, 2, 8);
				minRects[j].points(pts);//获取最小矩形的四个点坐标
				for (size_t t = 0; t < 4; t++)
				{
					line(dst, pts[t], pts[(t + 1) % 4], color, 2, 8, 0);
				}

			}
			
		}
	}
	imshow(output_win, dst);
	return;
}
