// ���������ε����߳��������������
// area = sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) )
// s = ( a + b + c) / 2

#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	double s, area;
    cout<<"�����������������߳���";
	cin >> a >> b >> c;
	s = (a + b + c) / 2;
	area = sqrt(s * (s - a) * (s - b) * (s - c));
	cout << "����������ǣ�" << area << endl;;
	return 0;
}