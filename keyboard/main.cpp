#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

vector<string> findWords(vector<string>& words);

class Solution {
public:
	vector<string> findWords(vector<string>& words) {
		vector<string> res;
		unordered_set<char> row1{ 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' };
		unordered_set<char> row2{ 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' };
		unordered_set<char> row3{ 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'Z', 'X', 'C', 'V', 'B', 'N', 'M' };
		for (string word : words) {
			int a = 0;
			int b = 0;
			int c = 0;
			for (char ch : word) {
				if (row1.count(ch)) a = 1;
				else if (row2.count(ch)) b = 1; //row2.count(ch���ж�row2������ch���ݣ��з���1���޷���0��
				else if (row3.count(ch)) c = 1;

				if (a + b + c > 1) break;
			}
			if (a + b + c > 1)
			    cout << "����ͬһ������" << endl;
			if (a + b + c == 1)
			{
				res.push_back(word);
				cout << "��ͬһ������" << endl;
			}
			
		}
		return res;
	}
};

void  main()
{
	vector<string> input,output;
	string str;
	Solution So;
	cout << "�����ַ���:" << endl;
	cin >> str;
	input.push_back(str);
	So.findWords(input);
}