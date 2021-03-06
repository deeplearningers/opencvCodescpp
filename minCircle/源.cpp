// 功能：代码 5-21 最小矩形与圆生成
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat img(500, 500, CV_8UC3);
	// 随机生成因子
	RNG& rng = theRNG();
	for (;;)
	{
		int i, count = rng.uniform(1, 101);
		vector<Point> points;
		// 随机生成二维点集
		for (i = 0; i < count; i++)
		{
			Point pt;
			pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
			pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
			points.push_back(pt);
		}
		// 二维点集计算出封闭一个倾斜最小面积的矩形
		RotatedRect box = minAreaRect(Mat(points));
		Point2f center, vtx[4];
		float radius = 0;
		// 来计算完全包围已有轮廓最小圆
		minEnclosingCircle(Mat(points), center, radius);
		box.points(vtx);
		img = Scalar::all(0);
		// 绘图圆显示
		for (i = 0; i < count; i++)
			circle(img, points[i], 3, Scalar(0, 0, 255), CV_FILLED, CV_AA);
		// 绘图线显示
		for (i = 0; i < 4; i++)
			line(img, vtx[i], vtx[(i + 1) % 4], Scalar(0, 255, 0), 1, CV_AA);
		circle(img, center, cvRound(radius), Scalar(0, 255, 255), 1, CV_AA);
		imshow("rect & circle", img);
		char key = (char)cvWaitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}
	return 0;
}
