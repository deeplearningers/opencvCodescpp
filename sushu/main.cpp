//#include"cstdio"
//#include"cstring"
//using namespace std;
//#define N 100//��N��Χ�ڵ�����
//int su[N], cnt; //�������������,�����ĸ�������
//int allshu[N]; //���������������
//void prime()
//{
//	cnt = 1;
//	memset(allshu, 1, sizeof(allshu));  //��ʼ����Ϊ��������������=1
//	allshu[0] = allshu[1] = 0;   //0��1��������=0
//	for (int i = 2; i <= N; i++)
//	{
//		//��������
//		if (allshu[i])
//		{
//			su[cnt++] = i;
//		}
//		for (int j = i * 2; j <= N; j += i)//�����ı�����Ϊ����
//		{
//			allshu[j] = 0;
//		}
//	}
//}
//int main()
//{
//	prime();
//	for (int i = 1; i < cnt; i++)
//		printf("%d\n", su[i]);
//	return 0;
//}

#include"cstdio"
#include"cstring"
using namespace std;
#define MAX 100//��MAX��Χ�ڵ�����
int su[MAX], cnt;
int isprime[MAX];
void prime()
{
	cnt = 1;
	memset(isprime, 1, sizeof(isprime));//��ʼ����Ϊ��������Ϊ����=1
	isprime[0] = isprime[1] = 0;//0��1��������
	for (int i = 2; i <= MAX; i++)
	{
		if (isprime[i])
			su[cnt++] = i;//��������i
		for (int j = 1; j < cnt&&su[j] * i < MAX; j++)
		{
			isprime[su[j] * i] = 0;//ɸ��С�ڵ���i��������i�Ļ����ɵĺ���
		}
	}
}
int main()
{
	prime();
	for (int i = 1; i < cnt; i++)
		printf("%d  ", su[i]);
	return 0;
}