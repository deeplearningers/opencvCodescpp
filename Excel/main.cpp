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
			res += (s[i - 1] - 'A' + 1) * tmp; //n=1��λ��n=2ʮλ*26,26����
			tmp *= 26;
		}
		return res;
	}
};

void  main()
{		
	string s;
	s ="AC";  //�ַ�����˫����
	int n = s.size();
	cout << n << endl;
	Solution So;
	int count = So.titleToNumber(s);
	cout << count << endl;
}