// testlleet.cpp : �������̨Ӧ�ó������ڵ㡣 
#include <iostream>  
using namespace std;
//����ṹ�岢��ʼ��
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void main()
{
	int n;
	cout << "Please inout n:";
	cin >> n;
	//ѭ�������ʼ��
	ListNode* head = new ListNode(1);
	ListNode* p = head;
	for (int i = 2; i <= n; i++)
	{
		ListNode* tmp = new ListNode(i);
		p->next = tmp;
		p = p->next;//��p�ƶ���nextλ��
	}
 	p->next = head; //ָ�뵽��ʼλ��
	//ѭ����ӡ
   	ListNode* q = head;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << q->val << " ";
			q = q->next;
		}
		cout << endl;
		q = q->next;//�˾�������Ǵ�ӡ����ʱ������һ������ʼ��ӡ
	}
	system("pause");
}