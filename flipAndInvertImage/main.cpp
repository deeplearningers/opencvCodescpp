#include <iostream>
#include <string>
#include <vector>
using namespace std;

//˵��: 1 <= A.length = A[0].length <= 20;   0 <= A[i][j] <= 1

vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A);

class Solution {
	public:
		vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
			for (int i = 0; i < A.size(); i++) {
				reverse(A[i].begin(), A[i].end());//���ú���
				for (int j = 0; j < A[i].size(); j++) {
					A[i][j] ^= 1;
				}
			}
			return A;
		}
};

void  main()
{
	int m,n,a;
	vector<int> mat1;
	vector<vector<int>>mat2,mat3;
	Solution So;
	cout << "�������Ľ���m��n:" << endl;
	cin >>m>>n;
	cout << "����m��n����:" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a;
			mat1.push_back(a);
		}
		mat2.push_back(mat1);
		mat1.clear();//mat1Ҫ�ǲ�ÿ����գ���һֱ�ǵ�һ��
	}
	cout << "��ӡ��mat2:" << endl;
	for (int k = 0; k < m;k++)
	{
		for (int q = 0; q < n; q++)
		{
			cout << mat2[k][q] << ' ';
		}
		cout << endl;
	}
	mat3 = So.flipAndInvertImage(mat2);
	cout << "��ӡ��mat3:" << endl;
	for (int l = 0; l < m; l++)
	{
		for (int p = 0; p < n; p++)
		{
			cout << mat3[l][p] << ' ';
		}
		cout << endl;
	}
}