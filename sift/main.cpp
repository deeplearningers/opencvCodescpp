// 功能：代码 8-3 SIFT 特征检测及匹配
// 作者：朱伟 zhu1988wei@163.com
// 来源：《OpenCV图像处理编程实例》
// 博客：http://blog.csdn.net/zhuwei1988
// 更新：2016-8-1
// 说明：版权所有，引用或摘录请联系作者，并按照上面格式注明出处，谢谢。
// 注解：需重新编译OpenCV3.1 contrib，见本书附录2
#include <opencv2/highgui//highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 计算图像的SIFT特征及匹配
cv::Mat cacSIFTFeatureAndCompare(cv::Mat srcImage1,
	cv::Mat srcImage2)
{
	CV_Assert(srcImage1.data != NULL && srcImage2.data != NULL);
	// 转换为灰度
	cv::Mat grayMat1, grayMat2;
	cv::cvtColor(srcImage1, grayMat1, CV_RGB2GRAY);
	cv::cvtColor(srcImage2, grayMat2, CV_RGB2GRAY);
	//归一化
	cv::normalize(grayMat1, grayMat1, 0, 255, cv::NORM_MINMAX);
	cv::normalize(grayMat2, grayMat2, 0, 255, cv::NORM_MINMAX);
	// 初始化SIFT检测描述子
	cv::SiftFeatureDetector detector;
	cv::SiftDescriptorExtractor extractor;
	// 关键点及特征描述矩阵声明
	vector<cv::KeyPoint> keyPoints1, keyPoints2;
	cv::Mat descriptorMat1, descriptorMat2;
	//特征点检测
	detector.detect(grayMat1, keyPoints1);
	detector.detect(grayMat2, keyPoints2);
	//特征描述矩阵求解
	extractor.compute(grayMat1, keyPoints1, descriptorMat1);
	extractor.compute(grayMat2, keyPoints2, descriptorMat2);

		// 计算特征匹配点
		cv::BruteForceMatcher<cv::L2<float>> matcher;
		vector< cv::DMatch > matches;
		matcher.match(descriptorMat1, descriptorMat2, matches);
		//二分排序
		int N = 80;
		nth_element(matches.begin(), matches.begin() + N - 1, matches.end());
		//去除特征点不匹配情况
		matches.erase(matches.begin() + N, matches.end());
		//绘制检测结果
		cv::Mat matchMat;
		cv::drawMatches(srcImage1, keyPoints1, srcImage2, keyPoints2, matches, matchMat);
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
	cv::Mat siftMat = cacSIFTFeatureAndCompare(srcImage1, srcImage2);
	cv::imshow("matchMat", siftMat);
	cv::waitKey(0);
	return 0;
}