#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src;
	src = imread("F:\\processImage\\leaf.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	//切换背景成黑色
	for (int row = 0; row < src.cols;row++)
	{
		for (int col = 0; col < src.rows;col++)
		{
			if (src.at<Vec3b>(col,row) == Vec3b(255,255,255))
			{
				src.at<Vec3b>(col, row)[0] = 0;
				src.at<Vec3b>(col, row)[1] = 0;
				src.at<Vec3b>(col, row)[2] = 0;
			}
		}
	}
	namedWindow("black background", CV_WINDOW_AUTOSIZE);
	imshow("black background", src);
	// Sharpen锐化
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	Mat imgLaplance;
	Mat sharpenImg = src;
	filter2D(src, imgLaplance, CV_32F, kernel, Point(-1, -1), 0, BORDER_DEFAULT);//自定义线性滤波
	src.convertTo(sharpenImg, CV_32F);
	Mat resultImg = sharpenImg - imgLaplance;  //相减的两个图像类型要一致
	resultImg.convertTo(resultImg, CV_8UC3);
	imgLaplance.convertTo(imgLaplance, CV_8UC3);
	src = resultImg;//copy back

	//转换为二值图像
	Mat binaryImg;
	cvtColor(src, resultImg, CV_BGR2GRAY);	
	threshold(resultImg, binaryImg, 40, 255, THRESH_BINARY | THRESH_OTSU); //全局自适应阈值
	imshow("binary image",binaryImg);
	//二值图像距离变换
	Mat distImg;
	distanceTransform(binaryImg, distImg, DIST_L1, 3, 5);
    //归一化
	normalize(distImg, distImg, 0, 1,NORM_MINMAX);
	imshow("distance result", distImg);
	//再次阈值二值化,腐蚀
	threshold(distImg, distImg, 0.4, 1, THRESH_BINARY);
	Mat k1 = Mat::zeros(13, 13, CV_8UC1);
	erode(distImg, distImg, k1, Point(-1, -1));
	imshow("distance binary image", distImg);

	//marker
	Mat dist_8u;
	distImg.convertTo(dist_8u, CV_8U);
	vector<vector<Point>> contours;
	//vector<Vec4i> hierarchy;
	findContours(dist_8u,contours,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(-1,-1));
	//creat mark
	Mat markers = Mat::zeros(src.size(), CV_32SC1);
	for (size_t i = 0; i < contours.size();i++)
	{
		drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i)+1),-1);
	}
	circle(markers, Point(5, 5), 3, Scalar(255, 255, 255), -1);
	imshow("my markers", markers * 1000);
	//perform watershed
	watershed(src, markers);
	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
	markers.convertTo(mark, CV_8UC1);
	bitwise_not(mark, mark, Mat());
	imshow("watershed image", mark);

	//generate random color
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size();i++)
	{
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
	//fill with color and display final result
	Mat dst = Mat::zeros(markers.size(), CV_8UC3);
	for (int row = 0; row < markers.cols;row++)
	{
		for (int col = 0; col < markers.rows;col++)
		{
			int index = markers.at<int>(col, row);
			if (index>0 && index <= static_cast<int>(contours.size())){
				dst.at<Vec3b>(col, row) = colors[index - 1];
		}
			else{
				dst.at<Vec3b>(col, row) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("final result", dst);

	cvWaitKey(0);
	return 0;
}