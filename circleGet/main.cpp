#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	const char* filename = "timg.jpg";

	Mat img = imread(filename);
	if (img.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}
	Mat img3, img2;
	//把彩色图转换为黑白图像
	cvtColor(img, img2, COLOR_BGR2GRAY);   
	GaussianBlur(img2, img2, Size(3, 3),2, 2);
	threshold(img2, img3, 210, 255, THRESH_BINARY);
	adaptiveThreshold(img3, img3, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 10);
	//// 形态学操作
	//Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));   // 构建形态学操作的结构元
	//morphologyEx(img3, img3, MORPH_CLOSE, kernel, Point(-1, -1));      //闭操作

	//kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));     // 构建形态学操作的结构元
	//morphologyEx(img3, img3, MORPH_OPEN, kernel, Point(-1, -1));                 //开操作
	// 寻找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	findContours(img3, contours, hireachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());

	Mat result_img = Mat::zeros(img.size(), CV_8UC3);     // 创建与原图同大小的黑色背景
	Point circle_center;              //定义圆心坐标
	for (auto t = 0; t < contours.size(); ++t)
	{
		// 面积过滤
		double area = contourArea(contours[t]);     //计算点集所围区域的面积
		if (area < 50 && contours.at(t).size()<10)            //晒选出轮廓面积大于100的轮廓
			continue;
		// 横纵比过滤
		Rect rect = boundingRect(contours[t]);            // 求点集的最小直立外包矩形
		float ratio = float(rect.width) / float(rect.height);        //求出宽高比

		if (ratio < 1.1 && ratio > 0.9)       //因为圆的外接直立矩形肯定近似于一个正方形，因此宽高比接近1.0
		{
			drawContours(result_img, contours, t, Scalar(0, 100, 100), -1, 8, Mat(), 0, Point());    ////在黑色背景图上画出圆，注意其中参数-1的意义
			printf("圆的面积: %f\n", area);
			double arc_length = arcLength(contours[t], true);         //计算点集所围区域的周长
			printf("圆的周长 : %f\n", arc_length);
			int x = rect.x + rect.width / 2;
			int y = rect.y + rect.height / 2;
			circle_center = Point(x, y);          //得到圆心坐标
			cout << "圆心坐标：" << "宽" << circle_center.x << " " << "高" << circle_center.y << endl;
			circle(result_img, circle_center, 2, Scalar(0, 255, 255), 2, 8, 0);
		}
	}
	waitKey();
	return 0;
}