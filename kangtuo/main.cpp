#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;

const int MAX_SIZE = 5;//��ǰ���е����ָ���

//���� MAX_SIZE �Ľ׳�
int fun(int m)
{ 
	int ret = 1;
	for (int i = 1; i <= m; i++)
	{
		ret =ret* i;
	}
	return ret;
}

//������չ����
//inΪ���������ansΪ�õ�������.
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
			if (i >MAX_SIZE || i < 0) { cout << "vetcor�±�Խ��" << endl; break; }
			cout << ans[i] << endl;
		}
}

//����չ��:
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
		printf("ans�ǣ� %d\n", ans);
	}
	ans ++;
	printf("����չ��ֵ�ǣ� %d\n", ans);
} 

int main()
{
	//int num;
	//vector<int>a;
	//cout << "����MAX_SIZE���������У������俵��չ��:" << endl;
	//while (cin >> num) {
	//	a.push_back(num);
	//	if (cin.get() == '\n')   //�����س�����ֹ
	//		break;
	//}
	//for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)
	//{
	//cout << *it;
	//}	cout << endl;
	//printf("��ȡֵ���� %d\n", a[0]);
	//getNumber(a);

		vector<int>array;
		int numb;
		cout << "����һ����,�����俵����չ����" << endl;
		cin >> numb;
		getArray(numb, array);

		putchar(10);
	return 0;
}