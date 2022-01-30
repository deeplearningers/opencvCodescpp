#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
//最近邻插值
//基于等间隔提取图像的缩放
Mat imageReduction1(Mat &srcImage, float kx, float ky)//原始图形以及缩放比例
{
	//获取输出图像分辨率
	int nRows = cvRound(srcImage.rows * kx);//cvRound这个函数返回的是和参数最接近的整数
	int nCols = cvRound(srcImage.cols * ky);
	Mat resultImage(nRows, nCols, srcImage.type());//创建一张输出的图像
	for (int i = 0; i < nRows; i++)
	{
		//根据水平因子计算在原图中的坐标
		int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
		for (int j = 0; j < nCols; j++)
		{
			//根据垂直因子计算在原图中的坐标
			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
			resultImage.at<Vec3b>(i, j) = srcImage.at<Vec3b>(x, y);
		}
	}
	return resultImage;
}
//基于区域子块提取图像缩放
//求每个区域子块中的像素的通道的平均值
Vec3b areaAverage(Mat &srcImage, Point_<int> leftPoint, Point_<int> rightPoint)
{

	int temp1 = 0, temp2 = 0, temp3 = 0;//用来保存区域块中的每个通道像素的和
	//计算区域块中的像素点的个数
	int nPix = (rightPoint.x - leftPoint.x + 1)*(rightPoint.y - leftPoint.y + 1);
	//计算区域子块中的各个通道的像素和
	for (int i = leftPoint.x; i <= rightPoint.x; i++)
	{
		for (int j = leftPoint.y; j <= rightPoint.y; j++)
		{
		   temp1 += srcImage.at<Vec3b>(i, j)[0];//求和区域块中的蓝绿红通道的像素和
			temp2 += srcImage.at<Vec3b>(i, j)[1];
			temp3 += srcImage.at<Vec3b>(i, j)[2];
		}
	}
	//对区域块中的每个通道求平均值
	Vec3b vecTemp;
	vecTemp[0] = temp1 / nPix;
	vecTemp[1] = temp2 / nPix;
	vecTemp[2] = temp3 / nPix;
	return vecTemp;
}
Mat imageReduction2(Mat &srcImage, float kx, float ky)
{
	//获取输出图像分辨率
	int nRows = cvRound(srcImage.rows * kx);//cvRound这个函数返回的是和参数最接近的整数
	int nCols = cvRound(srcImage.cols * ky);
	Mat resultImage(nRows, nCols, srcImage.type());//创建一张输出的图像
	//区域子块的左上角行列坐标
	int leftRowcoordinate = 0;
	int leftColcoordinate = 0;
	for (int i = 0; i < nRows; i++)
	{
		//根据水平因子计算在原图中的坐标
		int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
		for (int j = 0; j < nCols; j++)
		{
			//根据垂直因子计算在原图中的坐标
			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
			//求区域子块的均值
			resultImage.at<Vec3b>(i, j) = areaAverage(srcImage, Point_<int>(leftRowcoordinate, leftColcoordinate), Point_<int>(x, y));
			//更新下子块左上角的列坐标，行坐标不变
			leftColcoordinate = y + 1;
		}
		//一列循环完毕重新将列坐标置零
		leftColcoordinate = 0;
		//更新下子块左上角的行坐标
		leftRowcoordinate = x + 1;
	}
	return resultImage;
}

int main()

{
	Mat srcIamge = imread("F:\\processImage\\BaboonRGB.bmp");
	if (!srcIamge.data)
	{
		printf("image could not load...\n");
	return -1;
	}
	imshow("srcIamge", srcIamge);
	Mat resultImage1 = imageReduction1(srcIamge, 0.5, 0.5);
	imshow("res1", resultImage1);
	Mat resultImage2 = imageReduction2(srcIamge, 0.5, 0.5);
	imshow("res2", resultImage2);
	waitKey(0);
	return 0;
}