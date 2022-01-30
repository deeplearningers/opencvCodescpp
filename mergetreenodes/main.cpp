#include<stdio.h>
#include <STDLIB.H>


struct tree_node {
	int val;
	struct tree_node *left;
	struct tree_node *right;
	
};
 typedef struct tree_node *Tree;



 struct tree_node* mergeTrees(struct tree_node*t1, struct tree_node* t2) {
	if (t1&&t2){                                   //如果t1和t2都不是空结点，那么求结点值的和放到t1中
		t1->val += t2->val;
		t1->left = mergeTrees(t1->left, t2->left);   //t1的新的左子树就是对t1和t2的左子树的合并 
		t1->right = mergeTrees(t1->right, t2->right);//同上可得t1的右子树
		return t1;                                //返回t1
	}
	else if (!t1&&t2){                          //如果只有t2结点不空，那么返回t2结点
		return t2;
	}
	else if (!t1&&!t2){                         //如果两结点都为空，那么返回NULL；
		return NULL;
	}
	else{                                      //否则最后返回t1；
		return t1;
	}

}
 void CreateTree(Tree* T1){

	char ch; 
	scanf_s("%c", &ch);
	if (ch == '*')
	{
		*T1 = NULL;
	}
	else{
		*T1 = (Tree)malloc(sizeof(Tree));
		(*T1)->val = ch;
		CreateTree(&(*T1)->left);
		CreateTree(&(*T1)->right);
	}
}

//前序遍历
void PreShow(Tree T)

{
	if (!T)
	{
	  return;
	}
		printf("%c ", T->val);
		PreShow(T->left);
		PreShow(T->right);
}



void ClearTree(Tree *T)

{
	if (!*T){
	return;
	}
		ClearTree(&(*T)->left);
		ClearTree(&(*T)->right);
		free(*T);
		* T = NULL;
}




int main()
{
	Tree t1 ,t2 ;
	//printf("输入第一个二叉树的前序遍历序列，用*代替空节点：\n");
	CreateTree(&t1);
	PreShow(t1);
	CreateTree(&t2);
	PreShow(t2);
	mergeTrees(t1, t2);
	PreShow(t1);
}