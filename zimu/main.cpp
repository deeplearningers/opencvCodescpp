#include<iostream>
using  namespace std;
void print();
int main()
{
	print();

	return 0;
	system("pause");

}
void print()
{
	char a = 'A';
	cout << "��������ĸ" << endl;
	cin >> a;
	if (a != '#') print();
	if (a != '#') printf("%c", a);

}