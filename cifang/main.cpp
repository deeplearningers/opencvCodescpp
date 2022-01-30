#include <stdio.h>
#include <iostream>
using namespace std;

//int fun(int a, int b, int c)
//{
//	int ans=1;
//	if (b == 0) return 1 % c;
//	if (b == 1) return a % c;
//	ans = fun(a, b / 2, c);
//	ans = ans * ans % c;
//	if (b%2 == 1) ans = ans * a % c;//此句的作用是？？
//	return ans;
//}


int fun(int a, int b,int c)
{
	if (b == 1)
	    return a%c;
     int term = pow(a, b / 2);
         term = term*term%c;
	if (b % 2) //当b是奇数，乘以一个a
		term = a*term%c;
	    return term;
}

int main(void)
{
    int a, b, c,n;
	cout << "输入多少次:" << endl;
	cin >> n ; 
	while (n--)
	{
		cout << "输入a的b次幂对c求余数的abc:" << endl;
		cin >> a >> b >> c;
		cout << "a的b次幂对c求余数是：" <<fun(a,b,c) << endl;
	}
	return 0;
}
