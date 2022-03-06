#include <iostream>
using namespace std;

class Solution
{
public:
	int reverse(int x)
	{
		//x=1999999999
		long long ans = 0;
		const int maxint = 0x7fffffff;//0x7FFFFFFF 是long int的最大值
		const int minint = 0x80000000;//long int的最小值
		while (x!=0)
		{

			ans = ans * 10 + (x % 10);
			x /= 10;
		}
		if (ans>maxint||ans<minint)
		{

			ans = 0;
		}
		return ans;
	}
	int myatoi(string str)
	{
		const int maxint = 0x7fffffff;
		const int minint = 0x80000000;
		long long ans = 0;
		int st = 0;
		bool flag = false;

		while (st < str.length() && str[st] == ' ')
		{
			st++;
		}
		if (st < str.length() && str[st] == '+') st++;
		if (st < str.length() && str[st] == '-'){
			flag = true;
			st++;
		}
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] <= '9'&&str[i] >= '0')
			{
				ans = ans * 10 + str[i] - '0';
				if (ans>maxint) ans = maxint;
			}
			else{
				break;
			}
		}
		if (flag) ans = -ans;
		if (ans > maxint) ans = maxint;
		if (ans < minint) ans = minint;
		return ans;
	}



protected:
private:
};
//
//int main()
//{
//	Solution S;
//	int x,y;
//	cout << "输入x值:"<<endl;
//	cin >> x;
//	y=S.reverse(x);
//	cout << "y="<<y<<endl;
//	return 0;
//
//}


//int main()
//{
//	Solution S;
//	string str("999999");
//	int y;
//	y=S.myatoi(str);
//	cout << "y=" << y << endl;
//	return 0;
//}

class 
{
public:
	bool isPowerofTwo(int n){
		if (n <= 0) return 0;
		{
		}
	}
protected:
private:
};
int main()
{
	Solution S;
	string str("999999");
	int y;
	y = S.myatoi(str);
	cout << "y=" << y << endl;
	return 0;
}


