#include<stdio.h>
#include<iostream>
#define N 10
using namespace std;

void main()
{
	int a[N];
	int i, j, t;
	cout<<"������10�����֣�"<<endl;
	for (i = 0; i <10; i++)
		cin>>a[i];
	//ʹ������ѭ��
	for (i = 0; i < N - 1; i++)
	{
		for (j = 0; j< N - 1-i; j++)
		if (a[j]>a[j +1])//�Ƚϴ�С
		{
			t = a[j];
			a[j] = a[j + 1];
			a[j + 1] = t;
		}
	}
	cout<<"�����:"<<endl;
	for (i = 0; i < 10; i++)
		cout<<a[i]<<" ";
	cout << endl;
}