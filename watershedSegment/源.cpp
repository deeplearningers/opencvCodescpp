// ���ܣ����� 7-1-2 ��ˮ���㷨
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
// ��ˮ��ָ���ʾ
cv::Mat displaySegResult(cv::Mat & segments, int numOfSegments, cv::Mat & image)
{
	cv::Mat wshed(segments.size(), CV_8UC3);
	// ����������ɫ����
	vector<Vec3b> colorTab;
	for (int i = 0; i < numOfSegments; i++)
	{
		int b = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int r = theRNG().uniform(0, 255);
		colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
	//Ӧ�ò�ͬ��ɫ��ÿ������
	for (int i = 0; i < segments.rows; i++)
	{
		for (int j = 0; j < segments.cols; j++)
		{
			int index = segments.at<int>(i, j);
			if (index == -1)//��Ե
				wshed.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			else if (index <= 0 || index > numOfSegments)
				wshed.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			else
				wshed.at<Vec3b>(i, j) = colorTab[index - 1];
		}
	}
	if (image.dims > 0)
		wshed = wshed*0.5 + image*0.5;
	return wshed;
}
// �ָ�ϲ�
void segMerge(cv::Mat & image, cv::Mat & segments, int & numSeg)
{
	// ��һ���ָ�ֽ�������ͳ��
	vector<Mat> samples;
	// ͳ�����ݸ���
	int newNumSeg = numSeg;
	// ��ʼ���ָ��
	for (int i = 0; i <= numSeg; i++)
	{
		Mat sampleImage;
		samples.push_back(sampleImage);
	}
	// ͳ��ÿһ������
	for (int i = 0; i < segments.rows; i++)
	{
		for (int j = 0; j < segments.cols; j++)
		{
			// ���ÿ�����صĹ���
			int index = segments.at<int>(i, j);
			if (index > 0 && index <= numSeg)
			{
				samples[index].push_back(image(Rect(j, i, 1, 1)));
			}
		}
	}
	// ����ֱ��ͼ
	vector<MatND> hist_bases;
	Mat hsv_base;
	// ֱ��ͼ��������
	int h_bins = 35;
	int s_bins = 30;
	int histSize[] = { h_bins, s_bins };
	// hue �任��Χ 0 to 256, saturation �任��Χ0 to 180
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	// ʹ�õ�0��1ͨ��
	int channels[] = { 0, 1 };
	// ֱ��ͼ����
	MatND hist_base;
	for (int c = 1; c <= numSeg; c++)
	{
		if (samples[c].dims>0) {
			// �����򲿷�ת����hsv
			cvtColor(samples[c], hsv_base, CV_BGR2HSV);
			// ֱ��ͼͳ��
			calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
			// ֱ��ͼ��һ��
			normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());
			// ��ӵ�ͳ�Ƽ�
			hist_bases.push_back(hist_base);
		}
		else
		{
			hist_bases.push_back(MatND());
		}
		hist_base.release();
	}
	double similarity = 0;
	vector<bool> mearged;
	for (int k = 0; k < hist_bases.size(); k++)
	{
		mearged.push_back(false);
	}
	// ͳ��ÿһ�����ֵ�ֱ��ͼ����
	for (int c = 0; c<hist_bases.size(); c++)
	{
		for (int q = c + 1; q<hist_bases.size(); q++)
		{
			if (!mearged[q])
			{
				if (hist_bases[c].dims>0 && hist_bases[q].dims>0)
				{
					similarity = compareHist(hist_bases[c], hist_bases[q], CV_COMP_BHATTACHARYYA);
					if (similarity > 0.8)
					{
						mearged[q] = true;
						if (q != c)
						{
							//���򲿷ּ���
							newNumSeg--;
							for (int i = 0; i < segments.rows; i++)
							{
								for (int j = 0; j < segments.cols; j++)
								{
									int index = segments.at<int>(i, j);
									// �ϲ�
									if (index == q) {
										segments.at<int>(i, j) = c;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	numSeg = newNumSeg;
}
cv::Mat watershedSegment(cv::Mat & image, int & noOfSegments)
{
	cv::Mat gray;
	cv::Mat ret;
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	cv::imshow("Gray Image", gray);
	// ��ֵ����
	cv::threshold(gray, ret, 0, 255, CV_THRESH_BINARY_INV + CV_THRESH_OTSU);
	cv::imshow("Image after OTSU Thresholding", ret);
	// ��̬ѧ������
	cv::morphologyEx(ret, ret, MORPH_OPEN, Mat::ones(9, 9, CV_8SC1), Point(4, 4), 2);
	cv::imshow("Thresholded Image after Morphological open", ret);
	// ����任
	cv::Mat distTransformed(ret.rows, ret.cols, CV_32FC1);
	distanceTransform(ret, distTransformed, CV_DIST_L2, 3);
	// ��һ��
	normalize(distTransformed, distTransformed, 0.0, 1, NORM_MINMAX);
	cv::imshow("Distance Transformation", distTransformed);
	// ��ֵ���ָ�ͼ��
	threshold(distTransformed, distTransformed, 0.1, 1, CV_THRESH_BINARY);
	//��һ��ͳ��ͼ��0-255
	normalize(distTransformed, distTransformed, 0.0, 255.0, NORM_MINMAX);
	distTransformed.convertTo(distTransformed, CV_8UC1);
	cv::imshow("Thresholded Distance Transformation", distTransformed);
	//�����ǵķָ��
	int i, j, compCount = 0;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(distTransformed, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if (contours.empty())
		return Mat();
	Mat markers(distTransformed.size(), CV_32S);
	markers = Scalar::all(0);
	int idx = 0;
	// ���������
	for (; idx >= 0; idx = hierarchy[idx][0], compCount++)
		drawContours(markers, contours, idx, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
	if (compCount == 0)
		return Mat();
	//�����㷨��ʱ�临�Ӷ�
	double t = (double)getTickCount();
	watershed(image, markers);
	t = (double)getTickCount() - t;
	printf("execution time = %gms\n", t*1000. / getTickFrequency());
	Mat wshed = displaySegResult(markers, compCount, image);
	imshow("watershed transform", wshed);
	noOfSegments = compCount;
	return markers;
}


int main()
{
	cv::Mat srcImage = imread("..\\images\\sea.jpg");
	if (!srcImage.data)
		return 1;
	cv::imshow("Original Image", srcImage);
	// ת����hsvͼ��
	cv::Mat hsv;
	cv::cvtColor(srcImage, hsv, CV_BGR2HSV);
	cv::imshow("hsv", hsv);
	// ��ˮ�����
	int numOfSegments = 0;
	cv::Mat segments = watershedSegment(srcImage, numOfSegments);
	// �ָ�������ٹ��ָ�
	segMerge(srcImage, segments, numOfSegments);
	// ��ʾ�ָ�ͼ��
	cv::Mat wshed = displaySegResult(segments, numOfSegments, srcImage);
	// ��ʾ�ָ��ϲ�ͼ��
	cv::Mat wshedWithImage = displaySegResult(segments, numOfSegments, srcImage);
	cv::imshow("Merged segments", wshed);
	cv::imshow("Merged segments with image", wshedWithImage);
	cv::waitKey(0);
	return 0;
}

