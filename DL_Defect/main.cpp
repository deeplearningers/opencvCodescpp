#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	const char* filename = "3.bmp";
	Mat img = imread(filename);
	if (img.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}

	Mat imgGray;
	//把彩色图转换为黑白图像
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgGray, Size(3, 3), 0, BORDER_CONSTANT);

	cv::Mat edgeXMat, edgeYMat, edgeMat, edgeDL1, edgeDL2, edgeDL;
	//x方向边缘
	Sobel(imgGray, edgeXMat, CV_16S, 1, 0, 3, 1, 0, BORDER_CONSTANT);
	//y方向边缘
	Sobel(imgGray, edgeYMat, CV_16S, 0, 1, 3, 1, 0, BORDER_CONSTANT);
	//convertScaleAbs(edgeXMat, edgeXMat);//将图片转化成为8位图形进行显示 
	//convertScaleAbs(edgeYMat, edgeYMat);
	edgeYMat = abs(edgeYMat);
	subtract(edgeXMat, edgeYMat, edgeMat, Mat(), -1);
	convertScaleAbs(edgeMat, edgeMat);

	GaussianBlur(edgeMat, edgeMat, Size(3, 3), 0, BORDER_CONSTANT);
	//双阈值
	threshold(edgeMat, edgeDL1, 51, 255, THRESH_BINARY);
	threshold(edgeMat, edgeDL2, 90, 255, THRESH_BINARY_INV);

	cv::bitwise_and(edgeDL1, edgeDL2, edgeDL);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));     // 构建形态学操作的结构元
	//morphologyEx(edgeDL, edgeDL, MORPH_OPEN, kernel, Point(-1, -1));                 //开操作

	erode(edgeDL, edgeDL, kernel, Point(-1, -1), 1, 0, BORDER_DEFAULT);
	dilate(edgeDL, edgeDL, kernel, Point(-1, -1), 1, 0, BORDER_DEFAULT);

	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	findContours(edgeDL, contours, hireachy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point());

	RotatedRect rect;
	Point2f P[4];
	for (auto t = 0; t < contours.size(); ++t)
	{
		//drawContours(img, contours, t, Scalar(0,0,255), -1, 8, Mat(), 0, Point());
		rect = minAreaRect(contours.at(t));
		rect.points(P);
		for (int j = 0; j <= 3; j++)
		{
		line(img, P[j], P[(j + 1) % 4], Scalar(255), 1);
		}
	}
	waitKey();
	return 0;
}