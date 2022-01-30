#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char**argv)
{
	Mat src, gray_src, dst;
	src = imread("F:\\processImage\\PeppersRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	cvtColor(src, gray_src, CV_BGR2GRAY);
	int height = gray_src.rows;
	int width = gray_src.cols;
	//µ¥Í¨µÀ
	/*for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int gray = gray_src.at<uchar>(row, col);
			gray_src.at<uchar>(row, col) = 255-gray;
		}
	}
	imshow("output", gray_src);*/

	dst.create(src.size(), src.type());
	height = src.rows;
	width = src.cols;
	int nc = src.channels();
	for (int row = 0; row < height; row++)
	{
			for (int col = 0; col < width; col++)
		{
				if (nc == 1)
				
				{
					int gray = gray_src.at<uchar>(row, col);
					gray_src.at<uchar>(row, col) = 255 - gray;
				}
				else if(nc==3)
				{
					int b = src.at<Vec3b>(row, col)[0];
					int g = src.at<Vec3b>(row, col)[1];
					int r = src.at<Vec3b>(row, col)[2];
					dst.at<Vec3b>(row, col)[0] = 255 - b;
					dst.at<Vec3b>(row, col)[1] = 255 - g;
					dst.at<Vec3b>(row, col)[2] = 255 - r;
					gray_src.at<uchar>(row, col) = max(r, max(b, g));
				}
		}
	}
	bitwise_not(src,dst);
	imshow("output1", dst);
	imshow("output2", gray_src);


	cvWaitKey(0);
	return 0;
}