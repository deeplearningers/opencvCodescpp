// 功能：代码 2-28 LUT 查表反色处理
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
int main()
{
	// 源图像载入及判断
	cv::Mat srcImage = cv::imread("..\\images\\flower4.jpg");
	if (!srcImage.data)
		return 1;
	// 转换为灰度图像
	cv::Mat srcGray;
	cv::cvtColor(srcImage, srcGray, CV_RGB2GRAY);

	cv::namedWindow("srcImage");
	cv::imshow("srcImage", srcGray);

	int row = srcGray.rows;
	int col = srcGray.cols;
	cv::Mat tempImage = srcGray.clone();
	// 建立LUT 反色table
	uchar LutTable[256];
	for (int i = 0; i < 256; ++i)
		LutTable[i] = 255 - i;
	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* pData = lookUpTable.data;
	// 建立映射表
	for (int i = 0; i < 256; ++i)
		pData[i] = LutTable[i];
	// 应用索引表进行查找
	cv::LUT(srcGray, lookUpTable, tempImage);

	cv::namedWindow("dyn_threshold");
	cv::imshow("dyn_threshold", tempImage);
	cv::waitKey(0);
	return 0;
}
