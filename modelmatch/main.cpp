#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
Mat src,temp,dst;
int match_method = CV_TM_CCOEFF;
int max_track = 5;
void Match_demo(int ,void*);

int main(int argc, char**argv)
{
	src = imread("F:\\processImage\\模板匹配\\source.bmp"); //待检测图像
	temp = imread("F:\\processImage\\模板匹配\\template.bmp");//模板
	if (src.empty()||temp.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	imshow("input", src);
	imshow("template", temp);

	const char *trackbar_title = "Match Algol Type:";
	createTrackbar(trackbar_title, "input", &match_method, max_track, Match_demo);
	Match_demo(0,0);
	cvWaitKey(0);
	return 0;
}
void Match_demo(int, void*){
	
	int width = src.cols - temp.cols + 1;
	int height = src.rows-temp.rows + 1;
	Mat result(width, height, CV_32FC1);
	matchTemplate(src, temp, result, match_method, Mat());
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	Point minLoc;
	Point maxLoc;
	double min, max;
	src.copyTo(dst);
	Point tempLoc;
	minMaxLoc(result, &min, &max, &minLoc,&maxLoc, Mat());//返回的最值和最值的位置
	if (match_method==CV_TM_SQDIFF||match_method==CV_TM_SQDIFF_NORMED)
	{
		tempLoc = minLoc;
	}
	else{
		tempLoc = maxLoc;
	}
	//绘制矩形
	rectangle(dst, Rect(tempLoc.x, tempLoc.y, temp.cols, temp.rows), Scalar(0, 0, 0), 2, 8);
	rectangle(result, Rect(tempLoc.x, tempLoc.y, temp.cols, temp.rows), Scalar(0, 0, 0), 2, 8);
	imshow("result", result);
	imshow("match", dst);
}