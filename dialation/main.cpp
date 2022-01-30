#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src, dst;
int element_size = 3;
int max_size = 21;
void CallBack_Demo(int, void*);

int main(int argc, char**argv)
{

	src = imread("F:\\processImage\\PeppersRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	createTrackbar("ElementSize:", "output", &element_size, max_size, CallBack_Demo);
	CallBack_Demo(0, 0);
	
	cvWaitKey(0);
	return 0;
}
void CallBack_Demo(int, void*){
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
	cout << "形态学处理的矩阵核如下：" << endl << structureElement << endl;
	//dilate(src, dst, structureElement, Point(-1, -1), 1, 0);
	erode(src, dst, structureElement, Point(-1, -1));
	imshow("output", dst);
}