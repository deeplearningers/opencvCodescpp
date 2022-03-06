//#include"cstdio"
//#include"cstring"
//using namespace std;
//#define N 100//求N范围内的素数
//int su[N], cnt; //存放素数的数组,素数的个数变量
//int allshu[N]; //存放所有数的数组
//void prime()
//{
//	cnt = 1;
//	memset(allshu, 1, sizeof(allshu));  //初始化认为所有数都是素数=1
//	allshu[0] = allshu[1] = 0;   //0和1不是素数=0
//	for (int i = 2; i <= N; i++)
//	{
//		//保存素数
//		if (allshu[i])
//		{
//			su[cnt++] = i;
//		}
//		for (int j = i * 2; j <= N; j += i)//素数的倍数都为合数
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
#define MAX 100//求MAX范围内的素数
int su[MAX], cnt;
int isprime[MAX];
void prime()
{
	cnt = 1;
	memset(isprime, 1, sizeof(isprime));//初始化认为所有数都为素数=1
	isprime[0] = isprime[1] = 0;//0和1不是素数
	for (int i = 2; i <= MAX; i++)
	{
		if (isprime[i])
			su[cnt++] = i;//保存素数i
		for (int j = 1; j < cnt&&su[j] * i < MAX; j++)
		{
			isprime[su[j] * i] = 0;//筛掉小于等于i的素数和i的积构成的合数
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