#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

int uniqueMorseRepresentations(vector<string>& words) {
	string keys[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };
	set<string> res;
	for (int i = 0; i < words.size();i++)
	{
		string current = words[i];
		string temp = " ";
		for (int j = 0; j < current.length();j++)
		{
			temp = temp + keys[current[j] - 'a'];
		}
		res.insert(temp); //ÎÞÖØ¸´
	}
	return res.size();
}


int main()
{
	vector<string> words = { "boe", "zen", "gig", "msg" };
	int res = 0;
	res = uniqueMorseRepresentations(words);
	cout << res << endl;
	system("pause");
	return 0;
}