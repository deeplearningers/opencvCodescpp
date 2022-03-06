#include <iostream>
#include<opencv2/opencv.hpp>

//
//void main()
//{
//	int a, b, c, m, n;
//	printf_s("请输入所求的两个数\n");
//	scanf_s("%d%d", &a, &b);
//	m = a;
//	n = b;
//	c = a%b;
//	while (c)
//	{
//		a = b;
//		b = c;
//		c = a%b;
//	}
//	printf_s("%d和%d的最大公约数为:%d\n", m, n, b);
//	printf_s("\n");
//	cvWaitKey(0);
//	
//}


//void main()
//{
//	int a, b, c, m, n;
//	printf_s("请输入所求的两个数\n");
//	scanf_s("%d%d", &a, &b);
//	m = a;
//	n = b;
//	c = a - b;
//	while (c)
//	{
//		if (a > b)
//		{
//			c = a - b;
//		}
//		else if (a<b)
//		{
//			c = b - a;
//		}
//		else{
//			c = 0;
//		}
//		if (c){
//			a = b;
//			b = c;
//		}
//	}
//	printf_s("%d和%d的最大公约数为:%d\n", m, n, b);
//	printf_s("\n");
//	cvWaitKey(0);
//}

void main()
{
	int a, b, i, m, n;
	printf_s("请输入所求的两个数\n");
	scanf_s("%d%d", &a, &b);
	m = a;
	n = b;
	if (a>b)
	{
		i = b;
	}
	else{
		i = a;
	}
	for (i; i > 0;i--)
	{
		if (a%i==0 && b%i==0)
			break;
	}
	printf_s("%d和%d的最大公约数为:%d\n", m, n, i);
	printf_s("\n");
	cvWaitKey(0);
}