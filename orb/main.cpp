// 功能：代码 8-5 ORB 特征检测与匹配
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>

using namespace cv;
// 计算图像的ORB特征及匹配
cv::Mat cacORBFeatureAndCompare(cv::Mat srcImage1,
	cv::Mat srcImage2)
{
	CV_Assert(srcImage1.data != NULL && srcImage2.data != NULL);
	// 转换为灰度
	cv::Mat grayMat1, grayMat2;
	cv::cvtColor(srcImage1, grayMat1, CV_RGB2GRAY);
	cv::cvtColor(srcImage2, grayMat2, CV_RGB2GRAY);
	// 关键点检测
	std::vector<KeyPoint> keyPoints1, keyPoints2;

	Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);//均为默认参数

	orb->detect(srcImage1, keyPoints1);
	orb->detect(srcImage2, keyPoints2);
	// 描述特征向量
	cv::Mat descriptorMat1, descriptorMat2;
	orb->compute(srcImage1, keyPoints1, descriptorMat1);
	orb->compute(srcImage2, keyPoints2, descriptorMat2);

	// 特征匹配
	BFMatcher matcher(NORM_HAMMING);
	std::vector<DMatch> mathces;
	matcher.match(descriptorMat1, descriptorMat2, mathces);
	// 绘制匹配点集
	Mat matchMat;
	drawMatches(srcImage1, keyPoints1,
		srcImage2, keyPoints2, mathces, matchMat);
	//cv::imshow("Mathces", matchMat);
	return matchMat;
}
int main()
{
	// 读取源图像及待匹配图像
	cv::Mat srcImage1 =
		cv::imread("..\\images\\hand1.jpg", 1);
	if (srcImage1.empty())
		return -1;
	cv::Mat srcImage2 =
		cv::imread("..\\images\\hand3.jpg", 1);
	if (srcImage2.empty())
		return -1;
	cv::Mat  matchMat = cacORBFeatureAndCompare(srcImage1, srcImage2);
	cv::imshow("matchMat", matchMat);
	cv::waitKey(0);
	return 0;
}
