#include <iostream>
#include <string>
using namespace std;

string toLowerCase(string str);

class Solution {
public:
	string toLowerCase(string str) {

		for (int i = 0; i < str.size(); i++){
			if (str[i] >= 'A' && str[i] <= 'Z'){
				str[i] += 32;
			}
		}
		return str;
	}
};

void  main()
	{
		string str1, str2;
		Solution So;
		cout << "ÊäÈëstring:" << endl;
		cin >> str1;
		str2 = So.toLowerCase(str1);
		cout << "Êä³östring :" << str2 << endl;
	}