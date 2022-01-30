#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

Mat bgImage;
const char* drawdemo_win = "draw shape and text demo";
void Myline();
void MyRectangle();
void MyEllipse();//椭圆
void MyCircle();//圆
void MyPolygon();
void RandomLineDemo();

int main(int argc, char**argv)
{

	bgImage = imread("F:\\processImage\\LenaRGB.tif");
	if (bgImage.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	Myline();
    MyRectangle();
	MyEllipse();
	MyCircle();
	MyPolygon();
	putText(bgImage, "hello OPENCV", Point(110, 100), CV_FONT_BLACK, 1.0, Scalar(0, 0, 0),2,8);
	RandomLineDemo();
	namedWindow("drawdemo_win", CV_WINDOW_AUTOSIZE);
	imshow("drawdemo_win", bgImage);
	cvWaitKey(0);
	return 0;
}

void Myline(){
	Point p1 = Point(20, 30);
	Point p2;
	p2.x = 300;
	p2.y = 300;
	Scalar color = Scalar(255, 0, 0);//线的颜色，三通道来定义
	line(bgImage, p1, p2, color, 1, LINE_AA,0);
}
void MyRectangle(){
	Rect rect = Rect(200, 100, 300, 300);
	Scalar color = Scalar(255, 0, 0);
	rectangle(bgImage, rect, color, 2, LINE_8, 0);
}
void MyEllipse(){
	Scalar color = Scalar(255, 0, 0);
	ellipse(bgImage,Point(bgImage.cols/2,bgImage.rows/2),Size(bgImage.cols/4,bgImage.rows/2),90,0,180,color,1,LINE_8,0);
}
void MyCircle(){
	Scalar color = Scalar(255, 255, 0);
	Point center = Point(bgImage.cols / 2, bgImage.rows / 2);
	circle(bgImage, center, 50, color, 1, LINE_8, 0);
}
void MyPolygon(){
	Point pts[1][5];
	pts[0][0] = Point(100, 100);
	pts[0][1] = Point(100, 200);
	pts[0][2] = Point(200, 200);
	pts[0][3] = Point(200, 100);
	pts[0][4] = Point(100, 100);

	const Point* ppts[] = { pts[0] };
	int npt[] = { 5 };
	Scalar color = Scalar(255, 255,11);
	fillPoly(bgImage,ppts,npt,1,color,8);
}
void RandomLineDemo(){
	RNG rng(12345);
	Point pt1;
	Point pt2;
	pt1.x = rng.uniform(0, bgImage.cols);
	pt2.x = rng.uniform(0, bgImage.cols);
	pt1.y = rng.uniform(0, bgImage.rows);
	pt2.y = rng.uniform(0, bgImage.rows);
	Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	line(bgImage, pt1, pt2, color, 1, 8, 0);
}