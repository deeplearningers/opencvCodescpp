#include <iostream>
#include <string>
using namespace std;

int findComplement(int num);

class Solution {
public:
	int findComplement(int num) {
		int sum = 0, n = 0, Div = -1, Rem = 0;
		while (Div != 0)
		{
			Div = num / 2;  //终止条件
			Rem = num % 2;
			num = Div;
			sum += (1 - Rem)*pow(2, n);
			n++;
		}
		return sum;
	}
};

void  main()
{
	int num1 = 0;
	int num2 = 0;
	Solution So;
	cout << "输入要求补数的整数:" << endl;
	cin >> num1;
	num2= So.findComplement(num1);
	cout << "补数是：" << num2 << endl;
}