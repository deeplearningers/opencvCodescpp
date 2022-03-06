#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
	double x1, y1, x2, y2, x3, y3;
	cout << "输入六个坐标：x1, y1, x2, y2, x3, y3;" << endl;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	while (x1 != 0 || y1 != 0 || x2 != 0 || y2 != 0 || x3 != 0 || y3 != 0) {
		if ((x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1) > 0) cout << "ABC逆时针" << endl;
		else cout << "ABC顺时针" << endl;
		cout << "输入六个坐标：x1, y1, x2, y2, x3, y3;" << endl;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	}
	return 0;
}
