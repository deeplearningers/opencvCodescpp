/*
���ݣ�����Ԫ����������ΪCElemType�Ķ�̬˳��ṹ���Ա�����װ�Ա�Ĳ�������
���ߣ�zhaolong2
���ڣ�2018/6/7
*/

#include<iostream>
#include "CList.cpp"

using namespace std;


int main(int argc, char**argv)
{
	//���������ձ�
	CList <int> C1;
	CList <float> C2;
	//��ĳ�ʼ��Ϣ
	cout << "��ĳ�ʼ��Ϣ������ԣ�" << endl;
	cout << "C1��C2�ĳ�ʼ����Ϊ��" << C1.GetLength() << '\t' << C2.GetLength() << endl;
	cout << "C1��C2�ĳ�ʼ����Ϊ��" << C2.GetSize() << '\t' << C2.GetSize() << endl;
	cout << endl;

	//�ڱ��β������һЩԪ�ز���ʾ
	cout << "��Ԫ�����Ӳ��ԣ�" << endl;
	for (int i = 1; i <= 10; i++)
	{
		C1.AddTail(2 * i);
		C2.AddTail(i*i + 0.1);
	}
	cout << "C1����Ԫ��Ϊ:\n";
	C1.ShowValues();
	cout << "C2����Ԫ��Ϊ:\n";
	C2.ShowValues();
	cout << endl;

	//�ڱ��ָ��λ�ò���Ԫ�ز���ʾ
	cout << "��Ԫ�ز�����ԣ�" << endl;
	C1.InsertAt(5, 11);
	C2.InsertAt(7, 22.2);
	cout << "C1����Ԫ��Ϊ:\n";
	C1.ShowValues();
	cout << "C2����Ԫ��Ϊ:\n";
	C2.ShowValues();
	cout << endl;

	//��ʾ��ָ��λ�õ�Ԫ��
	cout << "��Ԫ���������ԣ�" << endl;
	cout << "C1��C2����5��Ӧ�Ľڵ��ֵ�ֱ�Ϊ��" << C1.GetAt(5) << '\t' << C2.GetAt(5) << endl;
	cout << endl;

	//ɾ������ָ��λ�õ�Ԫ��
	cout << "��Ԫ��ɾ�����ԣ�" << endl;
	C1.RemoveAt(3,2);
	C2.RemoveAt(4,1);
	cout << "C1����Ԫ��Ϊ:\n";
	C1.ShowValues();
	cout << "C2����Ԫ��Ϊ:\n";
	C2.ShowValues();
	cout << endl;


	system("pause");
	return 0;
}
