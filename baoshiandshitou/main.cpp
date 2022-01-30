#include <iostream>
#include <string>
using namespace std;

int numJewelsInStones(string J, string S);

class Solution {
public:
	int numJewelsInStones(string J, string S) {
		int i = 0;
		for (int j = 0; j < J.length(); j++) {
			for (int s = 0; s < S.length(); s++) {
				if (J[j] == S[s]) i++;
			}
		}
		return i;
	}
};

void  main()
{
	string BS ,ST ;//初始化问题？
	int count = 0;
	Solution So;
	cout << "输入代表宝石的string:" << endl;
	cin >> BS;
	cout << "输入代表石头的string:" << endl;
	cin >> ST;
	count = So.numJewelsInStones(BS,ST);
	cout << "石头ST中的宝石BS个数是" << count << endl;
}