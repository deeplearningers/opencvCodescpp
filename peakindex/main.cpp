#include <vector>
#include <iostream>

using namespace std;

int peakIndexInMountainArray(vector<int>& A) {

	int s1 = A.size();
	for (int i = 0; i<s1; i++)
	{
		if (A[i]>A[i + 1])//����ֻ��Ҫ�ҵ�������������ĵ㣬����������һֱ��1��ֱ���ҵ�������
			return i;
	}

}

int main()
{
	vector<int> Array = { 0, 2, 1, 0 };
	int j = peakIndexInMountainArray(Array);
	cout << "�嶥Ԫ���ǵ�" << j << "����" << endl;
}