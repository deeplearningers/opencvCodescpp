#include<stdio.h>
void main()
{
	int A[6] = { 5, 2, 4, 6, 1, 3 };
	int i, j, key;
	for (j = 1; j<6; j++)
	{
		key = A[j];//从右侧牌堆中抓一张key牌，key牌即手中抓的将要插入的牌
		i = j - 1;//与key牌左侧第一张牌比较
		while ((i >= 0) && (A[i]>key))//一直比较，将较小的牌移至左侧
		{
			A[i + 1] = A[i];
			i = i - 1;
		}//key牌此时一直在手中，未插入
		A[i + 1] = key;//插入key牌
	}
	for (i = 0; i < 6; i++)
	{
		printf("%d\n", A[i]);
	}
}
