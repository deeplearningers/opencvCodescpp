#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
//����ڲ�ֵ
//���ڵȼ����ȡͼ�������
Mat imageReduction1(Mat &srcImage, float kx, float ky)//ԭʼͼ���Լ����ű���
{
	//��ȡ���ͼ��ֱ���
	int nRows = cvRound(srcImage.rows * kx);//cvRound����������ص��ǺͲ�����ӽ�������
	int nCols = cvRound(srcImage.cols * ky);
	Mat resultImage(nRows, nCols, srcImage.type());//����һ�������ͼ��
	for (int i = 0; i < nRows; i++)
	{
		//����ˮƽ���Ӽ�����ԭͼ�е�����
		int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
		for (int j = 0; j < nCols; j++)
		{
			//���ݴ�ֱ���Ӽ�����ԭͼ�е�����
			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
			resultImage.at<Vec3b>(i, j) = srcImage.at<Vec3b>(x, y);
		}
	}
	return resultImage;
}
//���������ӿ���ȡͼ������
//��ÿ�������ӿ��е����ص�ͨ����ƽ��ֵ
Vec3b areaAverage(Mat &srcImage, Point_<int> leftPoint, Point_<int> rightPoint)
{

	int temp1 = 0, temp2 = 0, temp3 = 0;//��������������е�ÿ��ͨ�����صĺ�
	//����������е����ص�ĸ���
	int nPix = (rightPoint.x - leftPoint.x + 1)*(rightPoint.y - leftPoint.y + 1);
	//���������ӿ��еĸ���ͨ�������غ�
	for (int i = leftPoint.x; i <= rightPoint.x; i++)
	{
		for (int j = leftPoint.y; j <= rightPoint.y; j++)
		{
		   temp1 += srcImage.at<Vec3b>(i, j)[0];//���������е����̺�ͨ�������غ�
			temp2 += srcImage.at<Vec3b>(i, j)[1];
			temp3 += srcImage.at<Vec3b>(i, j)[2];
		}
	}
	//��������е�ÿ��ͨ����ƽ��ֵ
	Vec3b vecTemp;
	vecTemp[0] = temp1 / nPix;
	vecTemp[1] = temp2 / nPix;
	vecTemp[2] = temp3 / nPix;
	return vecTemp;
}
Mat imageReduction2(Mat &srcImage, float kx, float ky)
{
	//��ȡ���ͼ��ֱ���
	int nRows = cvRound(srcImage.rows * kx);//cvRound����������ص��ǺͲ�����ӽ�������
	int nCols = cvRound(srcImage.cols * ky);
	Mat resultImage(nRows, nCols, srcImage.type());//����һ�������ͼ��
	//�����ӿ�����Ͻ���������
	int leftRowcoordinate = 0;
	int leftColcoordinate = 0;
	for (int i = 0; i < nRows; i++)
	{
		//����ˮƽ���Ӽ�����ԭͼ�е�����
		int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
		for (int j = 0; j < nCols; j++)
		{
			//���ݴ�ֱ���Ӽ�����ԭͼ�е�����
			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
			//�������ӿ�ľ�ֵ
			resultImage.at<Vec3b>(i, j) = areaAverage(srcImage, Point_<int>(leftRowcoordinate, leftColcoordinate), Point_<int>(x, y));
			//�������ӿ����Ͻǵ������꣬�����겻��
			leftColcoordinate = y + 1;
		}
		//һ��ѭ��������½�����������
		leftColcoordinate = 0;
		//�������ӿ����Ͻǵ�������
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