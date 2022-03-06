#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
Mat src, dst, map_x, map_y;
int index = 0;
void update_map(void);

int main(int argc, char**argv)
{
	
	src = imread("F:\\processImage\\PeppersRGB.tif");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	//创建x y映射表空间
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);
	
	int c = 0;
	while (true)
	{
		c = waitKey(500);
		if ((char)c==27)
		{
			break;
		}
		index = c % 4;
		update_map();
		remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 255, 255));
		imshow("remap", dst);
	}

	return 0;
}
void update_map(void){
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols;col++)
		{
			switch (index)
			{
				//
			case  0:
				if (col>(src.cols*0.25) && col<(src.cols*0.75) && row>(src.rows*0.25) && row < (src.rows*0.75)){
					map_x.at<float>(row, col) = 2 * (col - (src.cols*0.25));
					map_y.at<float>(row, col) = 2 * (row - (src.rows*0.25));
				}
				else{
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
				break;
				//列首尾对调，行不变
			case 1:
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = row;
				break;
				//行首尾对调，列不变
			case 2:
				map_x.at<float>(row, col) = col;
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
				//行列首尾都对调
			case 3:
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			}
		}
	}
}