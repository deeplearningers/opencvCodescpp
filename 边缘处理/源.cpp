#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst;
	src = imread("F:\\processImage\\4.bmp");
	if (src.empty())
	{
		cout << "could not load image!" << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	int top = (int)0.5*src.rows;
	int bottom = (int)0.5*src.rows;
	int left = (int)0.5*src.cols;
	int right = (int)0.5*src.cols;
	RNG rng(12345);   //随机数产生器
	int borderType = BORDER_DEFAULT;
	
	int c = 0;
	//while (true){
		/*c = waitKey(50);
		if((char)c==27){
			break;
		}
		
		if ((char)c == 'r'){
			borderType = BORDER_REPLICATE;
		}
		else if ((char)c == 'w'){
			borderType = BORDER_WRAP;
		}
		else if ((char)c == 'c'){
			borderType = BORDER_CONSTANT;
		}
		else{
			borderType = BORDER_DEFAULT;
		}*/

		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
		copyMakeBorder(src, dst, top, bottom, left, right, BORDER_CONSTANT, color);
		imshow("output", dst);
	//}

	//GaussianBlur(src, dst, Size(5, 5), 0, 0, BORDER_CONSTANT);
	//imshow("output", dst);

	waitKey(0);
	return 0;
}