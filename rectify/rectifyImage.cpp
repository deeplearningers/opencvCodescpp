#pragma warning(disable: 4996)


#include <iostream>
#include <fstream>
#include <sstream>

#include <io.h>
#include <direct.h>



#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace cv;
using namespace std;

int rectifyImages(const char* ImageOrigFolderPath, const char* LutXFolderPath, const char* LutYFolderPath, const char* Type)
{
	char		inputPath[256];
	char		outputPath[256];
	char		internalPath[256];
	char		lut_X_Path[256];
	char		lut_Y_Path[256];
	string fileFilterStr;
	int		flag_internal = 0;
	int		inputSuffix = 0;
	int		outputSuffix = 0;
	int		frameStart = 0;
	int		frameEnd = 1;
	int		imgWidth = 1280;
	int		imgHeight = 960;

	memset(inputPath, 0, 256);
	memset(outputPath, 0, 256);
	memset(internalPath, 0, 256);
	memset(lut_X_Path, 0, 256);
	memset(lut_Y_Path, 0, 256);

	sprintf(inputPath, ImageOrigFolderPath);
	sprintf(lut_X_Path, LutXFolderPath);
	sprintf(lut_Y_Path, LutYFolderPath);

	//read LUT
	double* lut_X = NULL;
	double* lut_Y = NULL;
	lut_X = new double[imgWidth * imgHeight];
	lut_Y = new double[imgWidth * imgHeight];

	readLUTFromUbootBinFile(&imgWidth, &imgHeight, lut_X_Path, lut_X, lut_Y);

	//double* lut_X = readLUTFromBinFile(&imgWidth, &imgHeight, lut_X_Path);
	//double* lut_Y = readLUTFromBinFile(&imgWidth, &imgHeight, lut_Y_Path);



	if (strcmp(Type, "L") == 0) {
		strcat((char*)(fileFilterStr.c_str()), "*_l.bmp");
	}
	else {
		strcat((char*)(fileFilterStr.c_str()), "*_r.bmp");
	}

	Directory dir;
	vector<string> folderPaths = dir.GetListFolders(ImageOrigFolderPath, "*", true);
	vector<string> folderNames = dir.GetListFolders(ImageOrigFolderPath, "*", false);

	for (int i = 0; i < folderPaths.size(); i++)
	{
		vector<string> filePaths = dir.GetListFiles(folderPaths[i], (char*)(fileFilterStr.c_str()), true);
		vector<string> fileNames = dir.GetListFiles(folderPaths[i], (char*)(fileFilterStr.c_str()), false);

		char* newFolderPath = new char[256];
		memset(newFolderPath, 0, 256);
		strcat(newFolderPath, inputPath);
		strcat(newFolderPath, "/rect_");
		strcat(newFolderPath, folderNames[i].data());
		mkdir(newFolderPath);

		for (int j = 0; j < filePaths.size(); j++)
		{
			unsigned char* srcImgData = new unsigned char[imgWidth*imgHeight];
			//读取每一张图片信息
			int flag = readDataFromBmp(srcImgData, imgWidth, imgHeight, (char*)(filePaths[j].c_str()));
			if (flag < 0) return -1;//返回值小于0，图像错误

			//校正图像
			unsigned char* dstImgData = new unsigned char[imgWidth*imgHeight];
			imageCorrection_debug(srcImgData, (unsigned short)imgWidth, (unsigned short)imgHeight, lut_X, lut_Y, dstImgData);

			char* imageSavePath = new char[256];
			memset(imageSavePath, 0, 256);
			strcat(imageSavePath, newFolderPath);
			strcat(imageSavePath, "/");
			strcat(imageSavePath, (char*)(fileNames[j].c_str()));

			//char* numStrOut = new char[3 + 1];
			//memset(numStrOut, 0, 3 + 1);
			//Number2FixedDigitChar(j, 3, numStrOut);
			//strcat(imageSavePath, numStrOut);
			//strcat(imageSavePath, "-");
			//strcat(imageSavePath, Type);
			//strcat(imageSavePath, ".bmp");
			//保存校正后图像
			saveData2Bmp(dstImgData, imgWidth, imgHeight, imageSavePath);

			//release memory
			delete[]srcImgData;
			srcImgData = NULL;
			delete[]imageSavePath;
			imageSavePath = NULL;
			delete[]dstImgData;
			dstImgData = NULL;
		}

	}

	return 0;
}


int clearFolder(const char* folderPath)
{
	Directory dirRect;
	vector<string> fileNamesDel = dirRect.GetListFiles(folderPath, "*.bmp", false);
	for (int i = 0; i < fileNamesDel.size(); i++)
	{
		char imagePath[500];
		memset(imagePath, 0, 500);
		strcat(imagePath, folderPath);
		strcat(imagePath, fileNamesDel[i].c_str());
		remove(imagePath);
	}
	return 0;
}



int Number2FixedDigitChar(int num, int digitNum, char* fixedChar)
{
	if (int(num / pow(10, (double)digitNum)) > 1)
		return -1;

	if (fixedChar == NULL)
		return -2;

	fixedChar[digitNum] = '\0';

	char* tempNumC = new char[100];
	memset(tempNumC, 0, 100);
	sprintf(tempNumC, "%d", num);/**/

	int numLen = strlen(tempNumC);

	for (int i = 0; i < digitNum; i++)
		fixedChar[i] = '0';

	for (int i = 0; i < numLen; i++)
		fixedChar[digitNum - numLen + i] = tempNumC[i];

	delete[]tempNumC;
	tempNumC = NULL;

	return 1;
}

int saveData2Bmp(unsigned char* imageData, int width, int height, char* path)
{
	Mat image = Mat(height, width, CV_8UC1, imageData);
	imwrite(path, image);

	return 1;
}

int saveData2Hex(unsigned char* imageData, int width, int height, char* path)
{
	int n = 0;
	FILE* dataFile;

	dataFile = fopen(path, "w");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			fprintf(dataFile, "%02x ", imageData[n]);

			if (n % 16 == 15)
				fprintf(dataFile, "\n");

			n++;
		}
	}

	fclose(dataFile);

	return 1;
}

int saveData2Raw(unsigned char* imageData, int width, int height, char* path)
{
	int n = 0;
	FILE* dataFile;

	dataFile = fopen(path, "wb");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			fwrite(&imageData[n], sizeof(unsigned char), 1, dataFile);
			n++;
		}
	}

	fclose(dataFile);

	return 1;
}

int readDataFromBmp(unsigned char* imageData, int width, int height, char* path)
{
	Mat image;
	image = imread(string(path), 0);

	if (image.empty())
	{
		printf("----- Read image is wrong ! -----\n   1: The path is wrong.\n   2: Image is damaged.");
		return -1;
	}

	if (image.rows != height || image.cols != width)
	{
		printf("----- The size of input image is wrong ! -----");
		return -2;
	}

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			imageData[i*width + j] = image.ptr<unsigned char>(i)[j];//每张图像的像素赋值给imageData
		}
	}

	return 1;
}

int readDataFromHex(unsigned char* imageData, int width, int height, char* path)
{
	int n = 0;
	FILE *fp;

	fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("----- Can not open the file ! -----");
		return -1;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned char tempC;
			fscanf(fp, "%hhx ", &tempC);
			imageData[n] = tempC;

			if (n % 16 == 15)
				fscanf(fp, "\n");

			n++;
		}
	}

	fclose(fp);

	return 1;
}

int readDataFromRaw(unsigned char* imageData, int width, int height, char* path)
{
	int n = 0;
	FILE *fp;

	fp = fopen(path, "rb");

	if (fp == NULL)
	{
		printf("----- Can not open the file ! -----");
		return -1;
	}

	unsigned char tempC;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			fread(&tempC, sizeof(unsigned char), 1, fp);
			imageData[n] = tempC;
			n++;
		}
	}

	fclose(fp);

	return 1;
}

int readLUTFromFile(double* lut, int width, int height, char* path)
{
	int n = 0;
	FILE *fp;

	fp = fopen(path, "r");
	if (fp == NULL)
		return -1;

	unsigned short tempN = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fscanf(fp, "%hhx ", &tempN);
			lut[n] = FP(double(tempN) / 32.0, 5);

			if (n % 16 == 15)
				fscanf(fp, "\n");

			n++;
		}
	}


	fclose(fp);

	return 1;
}

double* readLUTFromBinFile(int* width, int* height, char* path)
{
	int n = 0;
	FILE *fp;

	fp = fopen(path, "rb");
	if (fp == NULL)
		return NULL;

	fread(width, sizeof(unsigned short), 1, fp);
	fread(height, sizeof(unsigned short), 1, fp);

	double* lut = new double[*width * *height];

	unsigned short tempF = 0.0f;

	for (int i = 0; i < *height; i++)
	{
		for (int j = 0; j < *width; j++)
		{
			fread(&tempF, sizeof(unsigned short), 1, fp);
			lut[n] = float(tempF) / 32;
			n++;
		}
	}


	fclose(fp);

	return lut;
}

int readLUTFromUbootBinFile(int* width, int* height, char* path, double* lut_X, double* lut_Y)
{
	int n = 0;
	FILE *fp;

	fp = fopen(path, "rb");
	if (fp == NULL)
		return NULL;

	unsigned short tempX = 0.0f;
	unsigned short tempY = 0.0f;

	for (int i = 0; i < *height; i++)
	{
		for (int j = 0; j < *width; j++)
		{
			fread(&tempX, sizeof(unsigned short), 1, fp);
			fread(&tempY, sizeof(unsigned short), 1, fp);
			lut_X[n] = float(tempX) / 32;
			lut_Y[n] = float(tempY) / 32;
			n++;
		}
	}


	fclose(fp);

	return 1;
}

double sign_vision(double inputNum)
{
	if (inputNum >= 0.0)
		return 1.0;
	else
		return -1.0;
}

double FP(double inputNum, int bitNum)
{
	double c1 = sign_vision(inputNum)*int(abs(inputNum)*std::pow((double)2, bitNum))*1.0 / std::pow((double)2, bitNum);
	return c1;
}

double PFP(double inputNum, int bitNum, int powerNum)
{
	double tempC = 1.0;
	for (int i = 0; i < powerNum; i++)
	{
		tempC = tempC*FP(inputNum, bitNum);
		tempC = FP(tempC, bitNum);
	}

	return tempC;
}

int  imageCorrection(unsigned char* srcImData, unsigned short width, unsigned short height,
	double* lut_X, double* lut_Y, unsigned char* dstImData)
{
	int				i = 0, j = 0;
	int				tempGt = 0;
	double			tempIdealX = 0.0;
	double			tempIdealY = 0.0;

	if (srcImData == NULL || width < 1 || height < 1)
		return -1;

	if (dstImData == NULL)
		return -3;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			tempIdealX = lut_X[i*width + j];
			tempIdealY = lut_Y[i*width + j];

			biLinear_3bit(srcImData, width, height, tempIdealX, tempIdealY, &tempGt);
			dstImData[i*width + j] = (unsigned char)(tempGt);
		}
	}

	return 1;
}

int  imageCorrection_debug(unsigned char* srcImData, unsigned short width, unsigned short height,
	double* lut_X, double* lut_Y, unsigned char* dstImData)
{
	int				i = 0, j = 0;
	int				tempGt = 0;
	double			tempIdealX = 0.0;//LUT表中x坐标
	double			tempIdealY = 0.0;//LUT表中y坐标

	if (srcImData == NULL || width < 1 || height < 1)
		return -1;

	if (dstImData == NULL)
		return -3;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			tempIdealX = lut_X[i*width + j];
			tempIdealY = lut_Y [i*width + j];
			//双线性插值
			biLinear(srcImData, width, height, tempIdealX, tempIdealY, &tempGt);

			dstImData[i*width + j] = (unsigned char)(tempGt);


			int    minX, minY, maxX, maxY;
			float  deltaX, deltaY;

			if (tempIdealX < 0)
				tempIdealX = 0;
			if (tempIdealY < 0)
				tempIdealY = 0;

			if (tempIdealX >= width - 1)
			{
				tempIdealX = width - 1;
				minX = (int)tempIdealX;
				maxX = minX;
				deltaX = 0;
			}
			else
			{
				minX = (int)tempIdealX;
				maxX = minX + 1;
				deltaX = tempIdealX - minX;
			}

			if (tempIdealY >= height - 1)
			{
				tempIdealY = height - 1;
				minY = (int)tempIdealY;
				maxY = minY;
				deltaY = 0;
			}
			else
			{
				minY = (int)tempIdealY;
				maxY = minY + 1;
				deltaY = tempIdealY - minY;
			}

		}
	}

	return 1;
}

//3-bit bilinear interpolation
//g0:left-top, g1:right-top, g2:left-bottom, g3:right-bottom
//@ : gt
//dx = deltaX, dy = deltaY
//
//     g0  dx   g1
//       +*****+
//       *******
//       **@**** dy
//       +*****+
//     g2       g3
int biLinear_3bit(unsigned char* srcImData, unsigned short width, unsigned short height, double idealX, double idealY, int* gt)
{
	int     tempG1, tempG2, tempGt;
	int     minX, minY, maxX, maxY;
	double  deltaX, deltaY;
	int     g0, g1, g2, g3;
	int     dX, dY;

	if (gt == NULL || srcImData == NULL || width < 1 || height < 1)
		return -1;

	/*if(idealX < 0 || idealY < 0 || idealX > width - 1 || idealY > height - 1)
	{
	(*gt) = 0;
	return 1;
	}*/

	if (idealX < 0)
		idealX = 0;
	if (idealY < 0)
		idealY = 0;
	if (idealX > width - 1)
		idealX = width - 1;
	if (idealY > height - 1)
		idealY = height - 1;

	minX = (int)idealX;
	minY = (int)idealY;
	deltaX = idealX - minX;
	deltaY = idealY - minY;

	if (deltaX < 0.0001)
		maxX = minX;
	else
		maxX = minX + 1;

	if (deltaY < 0.0001)
		maxY = minY;
	else
		maxY = minY + 1;


	g0 = srcImData[minY*width + minX];
	g1 = srcImData[minY*width + maxX];
	g2 = srcImData[maxY*width + minX];
	g3 = srcImData[maxY*width + maxX];

	if (deltaX < 0.5)
	{
		if (deltaX < 0.25)
		{
			if (deltaX < 0.125)
			{
				dX = 1;
				tempG1 = g0 + ((g1 - g0) >> 3);
				tempG2 = g2 + ((g3 - g2) >> 3);
			}
			else
			{
				dX = 2;
				tempG1 = g0 + ((g1 - g0) >> 2);
				tempG2 = g2 + ((g3 - g2) >> 2);
			}
		}
		else
		{
			if (deltaX < 0.375)
			{
				dX = 3;
				tempG1 = g0 + ((g1 - g0) >> 2) + ((g1 - g0) >> 3);
				tempG2 = g2 + ((g3 - g2) >> 2) + ((g3 - g2) >> 3);
			}
			else
			{
				dX = 4;
				tempG1 = g0 + ((g1 - g0) >> 1);
				tempG2 = g2 + ((g3 - g2) >> 1);
			}
		}
	}
	else
	{
		if (deltaX < 0.75)
		{
			if (deltaX < 0.625)
			{
				dX = 5;
				tempG1 = g0 + ((g1 - g0) >> 1) + ((g1 - g0) >> 3);
				tempG2 = g2 + ((g3 - g2) >> 1) + ((g3 - g2) >> 3);
			}
			else
			{
				dX = 6;
				tempG1 = g0 + ((g1 - g0) >> 1) + ((g1 - g0) >> 2);
				tempG2 = g2 + ((g3 - g2) >> 1) + ((g3 - g2) >> 2);
			}
		}
		else
		{
			if (deltaX < 0.875)
			{
				dX = 7;
				tempG1 = g0 + ((g1 - g0) >> 1) + ((g1 - g0) >> 2) + ((g1 - g0) >> 3);
				tempG2 = g2 + ((g3 - g2) >> 1) + ((g3 - g2) >> 2) + ((g3 - g2) >> 3);
			}
			else
			{
				dX = 8;
				tempG1 = g1;
				tempG2 = g3;
			}
		}
	}


	if (deltaY < 0.5)
	{
		if (deltaY < 0.25)
		{
			if (deltaY < 0.125)
			{
				dY = 1;
				tempGt = tempG1 + ((tempG2 - tempG1) >> 3);
			}
			else
			{
				dY = 2;
				tempGt = tempG1 + ((tempG2 - tempG1) >> 2);
			}
		}
		else
		{
			if (deltaY < 0.375)
			{
				dY = 3;
				tempGt = tempG1 + ((tempG2 - tempG1) >> 2) + ((tempG2 - tempG1) >> 3);
			}
			else
			{
				dY = 4;
				tempGt = tempG1 + ((tempG2 - tempG1) >> 1);
			}
		}
	}
	else
	{
		if (deltaY < 0.75)
		{
			if (deltaY < 0.625)
			{
				dY = 5;
				tempGt = tempG1 + ((tempG2 - tempG1) >> 1) + ((tempG2 - tempG1) >> 3);
			}
			else
			{
				dY = 6;
				tempGt = tempG1 + ((tempG2 - tempG1) >> 1) + ((tempG2 - tempG1) >> 2);
			}
		}
		else
		{
			if (deltaY < 0.875)
			{
				dY = 7;
				tempGt = tempG1 + ((tempG2 - tempG1) >> 1) + ((tempG2 - tempG1) >> 2) + ((tempG2 - tempG1) >> 3);
			}
			else
			{
				dY = 8;
				tempGt = tempG2;
			}
		}
	}

	(*gt) = tempGt;

	return 1;
}
//目标图像gt
int biLinear(unsigned char* srcImData, unsigned short width, unsigned short height, float idealX, float idealY, int* gt)
{
	double  tempG1, tempG2, tempGt;
	int    minX, minY, maxX, maxY;
	double  deltaX, deltaY;
	int    g0, g1, g2, g3;

	if (gt == NULL || srcImData == NULL || width < 1 || height < 1)
		return -1;

	if (idealX < 0)
		idealX = 0;
	if (idealY < 0)
		idealY = 0;
	//边缘上的x、y处理
	if (idealX >= width - 1)
	{
		idealX = width - 1;
		minX = (int)idealX;
		maxX = minX;
		deltaX = 0;
	}
	else
	{
		minX = (int)idealX;
		maxX = minX + 1;
		deltaX = idealX - minX;
	}

	if (idealY >= height - 1)
	{
		idealY = height - 1;
		minY = (int)idealY;
		maxY = minY;
		deltaY = 0;
	}
	else
	{
		minY = (int)idealY;
		maxY = minY + 1;
		deltaY = idealY - minY;
	}
	//
	deltaX = FP(deltaX, 5);
	deltaY = FP(deltaY, 5);


	g0 = srcImData[minY*width + minX];
	g1 = srcImData[minY*width + maxX];
	g2 = srcImData[maxY*width + minX];
	g3 = srcImData[maxY*width + maxX];

	tempG1 = g0*(1 - deltaX) + deltaX*g1;
	tempG2 = g2*(1 - deltaX) + deltaX*g3;
	tempGt = tempG1*(1 - deltaY) + deltaY*tempG2;

	(*gt) = (int)(tempGt);

	return 1;
}
