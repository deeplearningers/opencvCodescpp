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
	string BS ,ST ;//��ʼ�����⣿
	int count = 0;
	Solution So;
	cout << "�������ʯ��string:" << endl;
	cin >> BS;
	cout << "�������ʯͷ��string:" << endl;
	cin >> ST;
	count = So.numJewelsInStones(BS,ST);
	cout << "ʯͷST�еı�ʯBS������" << count << endl;
}