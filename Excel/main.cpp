#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	int titleToNumber(string s) {
		int n = s.size();
		int res = 0;
		int tmp = 1;
		for (int i = n; i >= 1; --i) {
			res += (s[i - 1] - 'A' + 1) * tmp; //n=1个位；n=2十位*26,26进制
			tmp *= 26;
		}
		return res;
	}
};

void  main()
{		
	string s;
	s ="AC";  //字符串用双引号
	int n = s.size();
	cout << n << endl;
	Solution So;
	int count = So.titleToNumber(s);
	cout << count << endl;
}