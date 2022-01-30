#include <iostream>


int hammingDistance(int x, int y) {

	int cnt = 0;
	x = x^y;
	while (x != 0)
	{
		if (x & 0x01)
			cnt++;
		x = x >> 1;
	}
	return cnt;

}

int main()
{
	int x=0, y=0,t=0; //初始化
	printf_s("输入两个数字: \n");
	scanf_s("%d%d", &x, &y); //加&&
	t=hammingDistance(x, y);
	printf_s("hamming distance is  %d\n",t);
	return 0;
}
