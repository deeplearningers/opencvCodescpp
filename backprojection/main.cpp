#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
Mat src, hsv, hue;
int bins = 10;
void Hist_And_Backprojection(int, void*);

int main(int argc, char**argv)
{
	
	src = imread("F:\\processImage\\hand.jpg");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	cvtColor(src, hsv, CV_BGR2HSV);
	hue.create(hsv.size(), hsv.depth());
	int nchannels[] = { 0, 0 }; //hsv�ĵ�1��ͨ����hue�ĵ�һ��ͨ��
	mixChannels(&hsv, 1, &hue, 1, nchannels, 1);//����hͨ����hue

	namedWindow("BackProj", CV_WINDOW_AUTOSIZE);
	createTrackbar("Hist-Bins", "BackProj", &bins, 180, Hist_And_Backprojection);
	Hist_And_Backprojection(0, 0);
	cvWaitKey(0);
	return 0;
}
void Hist_And_Backprojection(int, void*){
	float range[] = { 0, 180 };
	const float *histRanges = {range};
	Mat h_hist;
	calcHist(&hue, 1, 0, Mat(), h_hist, 1, &bins, &histRanges, true, false);
	normalize(h_hist, h_hist, 0, 255, NORM_MINMAX,-1, Mat());
	Mat backPrjImage;
	calcBackProject(&hue, 1, 0, h_hist, backPrjImage, &histRanges, 1, true);
	imshow("BackProj", backPrjImage);

	int hist_h = 500;
	int hist_w = 500;
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	int bin_w = (hist_w / bins);
	for (int i = 1; i < bins;i++)
	{
		rectangle(histImage, Point((i - 1)*bin_w, (hist_h - cvRound(h_hist.at<float>(i - 1)*(500 / 255)))),
			Point((i)*bin_w, (hist_h - cvRound(h_hist.at<float>(i)*(500 / 255)))), Scalar(0, 0, 255), -1);

	}
	imshow("histogram", histImage);

}