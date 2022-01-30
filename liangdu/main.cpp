#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst;
	src = imread("F:\\processImage\\LenaRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	cvtColor(src, src, CV_BGR2GRAY);
	char input_win[] = "input iamage";
	imshow(input_win, src);
	int height = src.rows;
	int width = src.cols;
	float alpha = 0.5;
	float beta = 100;
	dst = Mat::zeros(src.size(), src.type());
	Mat m1;
	src.convertTo(m1, CV_32F);
	for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++){
			if (src.channels() == 3){
				float b = m1.at<Vec3f>(row, col)[0];
				float g = m1.at<Vec3f>(row, col)[1];
				float r = m1.at<Vec3f>(row, col)[2];

				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b*alpha+beta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g*alpha + beta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r*alpha + beta);
			}
			else if (src.channels() == 1){
				float v = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = saturate_cast<uchar>(v*alpha+beta);
			}
		}
	}

	char output_title[] = "contrast and brightness change demo!";
	imshow(output_title,dst);



	cvWaitKey(0);
	return 0;
}