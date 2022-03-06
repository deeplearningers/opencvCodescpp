#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
Mat src, dst;

int main(int argc, char**argv)
{

	src = imread("F:\\processImage\\PeppersRGB.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	/*cvtColor(src, dst, CV_BGR2GRAY);
	equalizeHist(dst, dst);
	imshow("output", dst);*/
	//分离通道
	vector<Mat> bgr(2);
	split(src, bgr);
	
	//imshow("output", bgr[0]);
	//计算直方图
	int histSize = 256;
	float range[] = { 0, 255 };
	const float *histRanges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr[0], 1, 0,Mat(), b_hist,1, &histSize, &histRanges, true,false);
	calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRanges, true, false);
	//归一化-划到一定范围
	int hist_h = 400;
	int hist_w = 512;
	int bin_w = hist_w / histSize;
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(255, 255, 255));
	normalize(b_hist, b_hist,0,hist_h,NORM_MINMAX,-1,Mat());
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	//画出直方图
	for (int i = 1; i < histSize; i++){
		line(histImage, Point((i - 1)*bin_w,  cvRound(b_hist.at<float>(i - 1))),
			Point((i)*bin_w,cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);

		line(histImage, Point((i - 1)*bin_w, cvRound(g_hist.at<float>(i - 1))),
			Point((i)*bin_w, cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);

		line(histImage, Point((i - 1)*bin_w, cvRound(r_hist.at<float>(i - 1))),
			Point((i)*bin_w, cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
	}
	namedWindow("output1", CV_WINDOW_AUTOSIZE);
	imshow("output1", histImage);

	cvWaitKey(0);
	return 0;
}