#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;

const int MAX_SIZE = 5;//当前排列的数字个数

//计算 MAX_SIZE 的阶乘
int fun(int m)
{ 
	int ret = 1;
	for (int i = 1; i <= m; i++)
	{
		ret =ret* i;
	}
	return ret;
}

//康托逆展开：
//in为输入的数，ans为得到的排列.
void getArray(int in, vector<int>ans)
{
	    in--;
		bool vis[MAX_SIZE+1] = { 0 };
		for (int i = 0; i <MAX_SIZE; i++){
			int jie = fun(MAX_SIZE - 1 - i);
			int t = in / jie +1;
			in %= jie; 
			int k = 0;
			int j;
			for (j = 1; j <= MAX_SIZE; j++){
				if (!vis[j]) k++;
				if (k == t) break;
			}
			ans[i] = j;
			vis[j] = 1;			
		}

		for (size_t i = 0; i <MAX_SIZE; i++)
		{
			if (i >MAX_SIZE || i < 0) { cout << "vetcor下标越界" << endl; break; }
			cout << ans[i] << endl;
		}
}

//康托展开:
void getNumber(vector<int>in)
{
	int i,j,numOfMin,ans=0;
	for (i = 0; i < MAX_SIZE ; i++)
	{
		numOfMin = 0;
		for (j = i + 1; j < MAX_SIZE; j++)
		{
			if (in[j]< in[i])
				numOfMin++;
		}
		int jie = fun(MAX_SIZE - i - 1);
		ans += numOfMin*jie;
		printf("ans是： %d\n", ans);
	}
	ans ++;
	printf("康拓展开值是： %d\n", ans);
} 

int main()
{
	//int num;
	//vector<int>a;
	//cout << "输入MAX_SIZE个数的排列，计算其康拓展开:" << endl;
	//while (cin >> num) {
	//	a.push_back(num);
	//	if (cin.get() == '\n')   //遇到回车，终止
	//		break;
	//}
	//for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)
	//{
	//cout << *it;
	//}	cout << endl;
	//printf("读取值测试 %d\n", a[0]);
	//getNumber(a);

		vector<int>array;
		int numb;
		cout << "输入一个数,计算其康拓逆展开：" << endl;
		cin >> numb;
		getArray(numb, array);

		putchar(10);
	return 0;
}