#include<stdio.h>
void main()
{
	int A[6] = { 5, 2, 4, 6, 1, 3 };
	int i, j, key;
	for (j = 1; j<6; j++)
	{
		key = A[j];//���Ҳ��ƶ���ץһ��key�ƣ�key�Ƽ�����ץ�Ľ�Ҫ�������
		i = j - 1;//��key������һ���ƱȽ�
		while ((i >= 0) && (A[i]>key))//һֱ�Ƚϣ�����С�����������
		{
			A[i + 1] = A[i];
			i = i - 1;
		}//key�ƴ�ʱһֱ�����У�δ����
		A[i + 1] = key;//����key��
	}
	for (i = 0; i < 6; i++)
	{
		printf("%d\n", A[i]);
	}
}
