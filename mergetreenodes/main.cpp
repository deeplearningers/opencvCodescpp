#include<stdio.h>
#include <STDLIB.H>


struct tree_node {
	int val;
	struct tree_node *left;
	struct tree_node *right;
	
};
 typedef struct tree_node *Tree;



 struct tree_node* mergeTrees(struct tree_node*t1, struct tree_node* t2) {
	if (t1&&t2){                                   //���t1��t2�����ǿս�㣬��ô����ֵ�ĺͷŵ�t1��
		t1->val += t2->val;
		t1->left = mergeTrees(t1->left, t2->left);   //t1���µ����������Ƕ�t1��t2���������ĺϲ� 
		t1->right = mergeTrees(t1->right, t2->right);//ͬ�Ͽɵ�t1��������
		return t1;                                //����t1
	}
	else if (!t1&&t2){                          //���ֻ��t2��㲻�գ���ô����t2���
		return t2;
	}
	else if (!t1&&!t2){                         //�������㶼Ϊ�գ���ô����NULL��
		return NULL;
	}
	else{                                      //������󷵻�t1��
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

//ǰ�����
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
	//printf("�����һ����������ǰ��������У���*����սڵ㣺\n");
	CreateTree(&t1);
	PreShow(t1);
	CreateTree(&t2);
	PreShow(t2);
	mergeTrees(t1, t2);
	PreShow(t1);
}