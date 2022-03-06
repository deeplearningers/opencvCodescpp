/*
* File name  : Josephus.cpp
* Function   : 约瑟夫问题 C++实现
* Created on : 2016年5月11日
* Author     : beijiwei@qq.com
*/
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX 10
typedef struct{
	int order;
	int dead;
}People;

typedef struct {
	People array[MAX];
	int length;// cirrent size
	int alive;
}Circle;

int Circle_run(Circle &V, int total, int start, int interval);
int main(int argc, char** argv)
{
	int N, K, M;
	cout << "Please input total man number,begin,interval:" << endl;
	cin >> N >> K >> M;
	Circle one;

	cout << "The last live people is :" << Circle_run(one, N, K, M) << endl;
	return 0;
}

int Circle_run(Circle &V, int total, int start, int interval)
{
	int i = 0;
	int count = 1;

	if (total > MAX) {
		cout << "error, array will overflow." << endl;
	}
	for (i = 0; i < total; i++) {
		V.array[i].dead = 0;
		V.array[i].order = i;
	}
	V.length = i;
	V.alive = total;
	while (V.alive>1) {
		if (start == V.length)
			start = 0;

		if (count == interval && V.array[start].dead == 0)// kill the alive man
		{
			V.array[start].dead = 1;
			V.alive--;
			count = 1;
			start++;
			continue;
		}

		if (V.array[start].dead == 1) {// jump dead
			start++;
			continue;
		}
		count++;
		start++;
	}

	for (int i = 0; i < total; i++) {
		if (V.array[i].dead == 0)
			return i;
	}

}