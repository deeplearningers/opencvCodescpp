#include<stdio.h>
#include<iostream> 


using namespace std;
typedef char ElemType;

typedef struct BiTNode{

	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*bitree;


//创建一个二叉树,约定用户遵照前序遍历方式输入数据
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