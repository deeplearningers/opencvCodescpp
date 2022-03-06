#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst;
	src = imread("F:\\processImage\\source.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	/*namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);*/

	medianBlur(src, dst, 3);
	cvtColor(dst, dst, CV_BGR2GRAY);
	vector<	Vec3f> pcircles;
	HoughCircles(dst, pcircles, CV_HOUGH_GRADIENT, 1, 10, 100, 100, 0, 0);

	//src.copyTo(dst);
	
	for (size_t i = 0; i < pcircles.size();i++)
	{
		//»æÖÆÔ²
		Point center = Point(cvRound(pcircles[i][0]), cvRound(pcircles[i][1]));
		int radius = cvRound(pcircles[i][2]);
		circle(src, center, radius, Scalar(0, 0, 255), 1, LINE_AA);
		circle(src, center, 1, Scalar(0, 255, 0), 1, LINE_AA);
	}
	
	imshow("output", src);
	cvWaitKey(0);
	return 0;
}