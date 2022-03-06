#include<stdio.h>
#include<stdlib.h>
#define N 10
typedef struct BinTreeNode
{
	int data;
	struct BinTreeNode *left;
	struct BinTreeNode *right;
}BinTreeNode, *BinTree;


BinTree insert(BinTree T, int data);//二叉树节点的添加
int TreeDepth(BinTree T);//返回树的深度(高度)

int main()
{
	int i = 0;
	int data[N] = { 20, 15, 10, 12, 18, 25, 30, 16, 17, 18 };
	BinTreeNode *root = NULL;
	int Depth = 0;
	for (i = 0; i < N; i++)
	{
		root = insert(root, data[i]);
	}
	Depth = TreeDepth(root);
	printf("\nTree Depth is %d.\n", Depth);
	free(root);
	return 0;
}
//注意理解递归
int TreeDepth(BinTree T)
{
	int rightdep = 0;
	int leftdep = 0;
	if (T == NULL)
		return -1;
	if (T->left != NULL)
		leftdep = TreeDepth(T->left);
	else
		leftdep = -1;
	if (T->right != NULL)
		rightdep = TreeDepth(T->right);
	else
		rightdep = -1;
	return (rightdep > leftdep) ? rightdep + 1 : leftdep + 1;
}
BinTree insert(BinTree T, int data)
{
	if (T == NULL)
	{
		T = (BinTree)malloc(sizeof(BinTreeNode));
		if (T == NULL)
			printf("Out of space!\n");
		else
		{
			T->data = data;
			T->left = NULL;
			T->right = NULL;
		}
	}
	else
	{
		if (data < T->data)
			T->left = insert(T->left, data);
		else
			T->right = insert(T->right, data);
	}
	return T;
}// { 20, 15, 10, 12, 18, 25, 30, 16, 17, 18 };