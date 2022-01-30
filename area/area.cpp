// 给出三角形的三边长，求三角形面积
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
    cout<<"请输入三角形三个边长：";
	cin >> a >> b >> c;
	s = (a + b + c) / 2;
	area = sqrt(s * (s - a) * (s - b) * (s - c));
	cout << "三角形面积是：" << area << endl;;
	return 0;
}