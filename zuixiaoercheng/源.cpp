/*#include <iostream>    
#include <algorithm>    
#include <valarray> */   
//#include <vector>    
//using namespace std;
//
//int main()
//{
//
//double x[] = { 1, 2, 3, 4, 5, 6 };
//double y[] = { 3, 5.5, 6.8, 8.8, 11, 12 };
//	valarray<double> data_x(x, 6);
//	valarray<double> data_y(y, 6);
//
//	float A = 0.0;
//	float B = 0.0;
//	float C = 0.0;
//	float D = 0.0;
//	A = (data_x*data_x).sum();  
//	B = data_x.sum();          
//	C = (data_x*data_y).sum();   
//	D = data_y.sum();
//	float tmp = A*data_x.size() - B*B;
//	float k, b;
//	k = (C*data_x.size() - B*D) / tmp;//��1
//	b = (A*D - C*B) / tmp;//��0
//	cout << "y=" << k << "x+" << b << endl;
//	return 0;
//}



#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "vector"
using namespace std;
struct point
{
   double x;
   double y;
};

typedef vector<double> doubleVector;
vector<point> getFile(char *File);  //��ȡ�ļ�����
doubleVector getCoeff(vector<point> sample, int n);   //���󷽳�

void main()
{
	int i, n;
	char *File = "XY.txt";
	vector<point> sample;
	doubleVector  coefficient;
	sample = getFile(File);
	printf("��϶���ʽ����n=");
	scanf_s("%d", &n);
	coefficient = getCoeff(sample, n);
	printf("\n��Ͼ����ϵ��Ϊ��\n");
	for (i = 0; i < coefficient.size(); i++)
		printf("a%d = %lf\n", i, coefficient[i]);
}

//���󷽳�
doubleVector getCoeff(vector<point> sample, int n)
{
	vector<doubleVector> matFunX;  //��ʽ3�����
	vector<doubleVector> matFunY;  //��ʽ3�Ҿ���
	doubleVector temp;
	double sum;
	int i, j, k;
	//��ʽ3�����
	for (i = 0; i <= n; i++)
	{
		temp.clear();
		for (j = 0; j <= n; j++)
		{
			sum = 0;
			for (k = 0; k < sample.size(); k++)
				sum += pow(sample[k].x, j + i);  //pow������ָ��
			temp.push_back(sum);
		}
		matFunX.push_back(temp);
	}

//��ʽ3�Ҿ���
for (i = 0; i <= n; i++)
	{
		temp.clear();
		sum = 0;
		for (k = 0; k < sample.size(); k++)
			sum += sample[k].y*pow(sample[k].x, i);
		temp.push_back(sum);
     	matFunY.push_back(temp);
	}
	printf("matFunY.size=%d\n", matFunY.size());
	//��������ʽ�任
	double num1, num2, ratio;
	for (i = 0; i < matFunX.size() - 1; i++)
	{
		num1 = matFunX[i][i];
		for (j = i + 1; j < matFunX.size(); j++)
		{
			num2 = matFunX[j][i];
			ratio = num2 / num1;
			for (k = 0; k < matFunX.size(); k++)
				matFunX[j][k] = matFunX[j][k] - matFunX[i][k] * ratio;
			matFunY[j][0] = matFunY[j][0] - matFunY[i][0] * ratio;
		}
	}
	//����������ߵ�ϵ��
  doubleVector coeff(matFunX.size(), 0);
	for (i = matFunX.size() - 1; i >= 0; i--)
	{
		if (i == matFunX.size() - 1)
			coeff[i] = matFunY[i][0] / matFunX[i][i];
		else
		{
			for (j = i + 1; j < matFunX.size(); j++)
				matFunY[i][0] = matFunY[i][0] - coeff[j] * matFunX[i][j];
			coeff[i] = matFunY[i][0] / matFunX[i][i];
		}
	}
	return coeff;
}
//��ȡ�ļ�����
vector<point> getFile(char *File)
{
	int i = 1;
    vector<point> dst;
	FILE *fp = fopen(File, "r");  //r����ֻ��
	if (fp == NULL)
{
		printf("Open file error!!!\n");
		exit(0);
}

	point temp;
	double num;
	while (fscanf(fp, "%lf", &num) != EOF)  //End Of File
	{

		if (i % 2 == 0)
		{
			temp.y = num;
			dst.push_back(temp);
		}
		else
			temp.x = num;
		i++;
	}

	fclose(fp);
	return dst;
}