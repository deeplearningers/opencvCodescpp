// testlleet.cpp : 定义控制台应用程序的入口点。 
#include <iostream>  
using namespace std;
//定义结构体并初始化
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
	//循环链表初始化
	ListNode* head = new ListNode(1);
	ListNode* p = head;
	for (int i = 2; i <= n; i++)
	{
		ListNode* tmp = new ListNode(i);
		p->next = tmp;
		p = p->next;//将p移动到next位置
	}
 	p->next = head; //指针到开始位置
	//循环打印
   	ListNode* q = head;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << q->val << " ";
			q = q->next;
		}
		cout << endl;
		q = q->next;//此句的作用是打印下行时，从下一个数开始打印
	}
	system("pause");
}