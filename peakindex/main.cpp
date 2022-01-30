#include <vector>
#include <iostream>

using namespace std;

int peakIndexInMountainArray(vector<int>& A) {

	int s1 = A.size();
	for (int i = 0; i<s1; i++)
	{
		if (A[i]>A[i + 1])//我们只需要找到满足这个条件的点，如果不满足就一直加1，直到找到并返回
			return i;
	}

}

int main()
{
	vector<int> Array = { 0, 2, 1, 0 };
	int j = peakIndexInMountainArray(Array);
	cout << "峰顶元素是第" << j << "个。" << endl;
}