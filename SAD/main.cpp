
#include "stdafx.h"
#include"SAD.h"
int _tmain(int argc, _TCHAR* argv[])
{
		Mat Img_L = imread("imL.png", 0)
		Mat Img_R = imread("imR.png", 0);
		Mat Disparity;    // ”≤ÓÕº
		//SAD mySAD;


		12

		SAD mySAD(7, 30);


	13

		Disparity = mySAD.computerSAD(Img_L, Img_R);


	14




		15

		imshow("Img_L", Img_L);


	16

		imshow("Img_R", Img_R);


	17

		imshow("Disparity", Disparity);


	18

		waitKey();


	19

		return 0;


	20

}


