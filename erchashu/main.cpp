#include<stdio.h>
#include<iostream> 


using namespace std;
typedef char ElemType;

typedef struct BiTNode{

	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*bitree;


//����һ��������,Լ���û�����ǰ�������ʽ��������
CreatBiTree(BiTNode*T)
{
	char c;
	scanf("%c", c);
	if (" " == c){
		*T = NULL;
	}
	else{
		*T = (BiTNode*)malloc(sizeof(BiTNode));
	}

}