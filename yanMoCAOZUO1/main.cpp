#include<opencv2\opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;

int main(int argc, char**argv){
	Mat src, dst;
	src = imread("F:\\processImage\\LenaRGB.bmp");
	if (!src.data)
	{
		printf("no data!");
		return -1;
	}
	namedWindow("原图像", CV_WINDOW_AUTOSIZE);
	imshow("原图像", src);

	int cols = (src.cols-1)*src.channels();
	int rows = src.rows;
	int offsetx = src.channels();
	dst = Mat::zeros(src.size(), src.type());

	/*for (int row = 1; row < (rows - 1); row++)
	{
		const uchar* current= src.ptr<uchar>(row);
		const uchar* privious = src.ptr<uchar>(row - 1);
		const uchar *next = src.ptr<uchar>(row + 1);
		uchar *output = dst.ptr<uchar>(row);

		for (int col = offsetx; col < cols - 1; col++)
		{
			output[col] =saturate_cast<uchar>( 5 * current[col] - (current[col - offsetx] + current[col + offsetx] + privious[col] + next[col]));
		}
	}*/ 

	Mat kernel = (Mat_<char>(3, 3) << 
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0);//-1与原图一致

	double t = getTickCount();
	filter2D(src, dst, -1, kernel);//掩模操作API
	double timeconsume = (getTickCount() - t) *1000/ getTickFrequency();// ms
	printf("time consume %.2f\n", timeconsume);
	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	imshow("dst", dst);

	waitKey(0);
	return 0;  

}