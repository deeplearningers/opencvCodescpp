#include <iostream>
using namespace std;
int binary_research(int arry[], int left, int right, int element)
{
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (arry[mid] > element)
		{
			right = mid - 1;
		}
		else if (arry[mid] < element)
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return element;
}
int main()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int right = sizeof(array)-1;//定义右下标并初始化
	int left = 0;//定义左下标并初始化为0
	int element = 0;//定义查找的元素并初始化为0
	cout<<"请输入要查找的元素:";
	cin >> element;
	int location = binary_research(array, left, right, element);
	if (location >= 0)
		cout << "The element's location is " << location << endl;
	else
		cout<<"Don't exit this element";
	return 0;
}