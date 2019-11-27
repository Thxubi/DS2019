#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSSIZE 100

typedef struct bitnode {
	char data;
	struct bitnode *lchild, *rchild;
} BiTNode, *BiTPtr;

int CreateBiT(BiTPtr *T);
void showBiT(BiTPtr Tree);
void printtab(int n);
void showl(BiTNode T, int n);
void showr(BiTNode T, int n);
void pres(BiTPtr T);
void ins(BiTPtr T);
void posts(BiTPtr T);
void swapBiT(BiTPtr *T, int slen);
int leafnum(BiTPtr T);

int main()
{
	int slen;
	BiTNode *Tree;					//Tree为BiTNode数组的头指针 
	slen = CreateBiT(&Tree);
	printf("BiTree\n");
	showBiT(Tree);
	printf("pre_sequence  : ");
	pres(&Tree[0]);
	printf("\nin_sequence   : ");
	ins(&Tree[0]);
	printf("\npost_sequence : ");
	posts(&Tree[0]);
	printf("\nNumber of leaf: %d\n", leafnum(&Tree[0])); 
	swapBiT(&Tree, slen);
	printf("BiTree swapped\n");
	showBiT(Tree);
	printf("pre_sequence  : ");
	pres(&Tree[0]);
	printf("\nin_sequence   : ");
	ins(&Tree[0]);
	printf("\npost_sequence : ");
	posts(&Tree[0]);
	printf("\n");
	return 0;
}

int leafnum(BiTPtr T)
{
	int n = 0;
	if(T == NULL)
		return 0;
	else if(T->data != '#' && T->lchild == NULL && T->rchild == NULL)
		n++;
	else if(T->data != '#' && (T->lchild->data == '#' && T->rchild->data == '#'))
		n++;
	else
	{
		n += leafnum(T->lchild);
		n += leafnum(T->rchild);
	}
	return n;
}
void ins(BiTPtr T)
{
	if(T == NULL)
		return;
	else
	{
		ins(T->lchild);
		if(T->data != '#')
			printf("%c", T->data);
		ins(T->rchild);
	}
}
void posts(BiTPtr T)
{
	if(T == NULL)
		return;
	else
	{	
		
		posts(T->lchild);
		posts(T->rchild);
		if(T->data != '#')
			printf("%c", T->data);
	}
}
void pres(BiTPtr T)
{
	if(T == NULL)
		return;
	else
	{
		if(T->data != '#')
			printf("%c", T->data);
		pres(T->lchild);
		pres(T->rchild);
	}
}

void swapBiT(BiTPtr *T, int slen)
{
	for(int i = 0; i <= (slen/2)-1; i++)
	{
		(*T)[i].rchild = &((*T)[2*i+1]);
		if(2*i+2 <= slen-1)
			(*T)[i].lchild = &((*T)[2*i+2]);
		else
			(*T)[i].lchild = NULL;
	}
}
void showBiT(BiTPtr Tree)
{
	int n = 0;
	if(Tree[0].data != '#')
		printf("%c\n", Tree[0].data);
	if(Tree[0].lchild != NULL)
		showl(Tree[0], n);
	if(Tree[0].rchild != NULL)
		showr(Tree[0], n);
}
void showl(BiTNode T, int n)
{
	
	T = *T.lchild;
	if(T.data != '#')
	{
		printtab(++n);
		printf("%c\n", T.data);
	}
	else
	{
		n++;
	}
	if(T.lchild != NULL)
		showl(T, n);
	if(T.rchild != NULL)
		showr(T, n);
}
void showr(BiTNode T, int n)
{
	T = *T.rchild;
	if(T.data != '#')
	{
		printtab(++n);
		printf("%c\n", T.data);
	}
	else
		n++;
	if(T.lchild != NULL)
		showl(T, n);
	if(T.rchild != NULL)
		showr(T, n);
}
void printtab(int n)
{
	for(int i = 0; i < n; i++)
		printf("    ");
}

int CreateBiT(BiTPtr *T)
{
	char S[MAXSSIZE+1];
	gets(S);				//数组输入
	int slen = strlen(S);
		
	*T = (BiTPtr)malloc(sizeof(BiTNode)*(slen+1));
	
	for(int i = 0; i < slen; i++)
	{
		(*T)[i].data = S[i];
		(*T)[i].lchild = NULL;
		(*T)[i].rchild = NULL;
	}
	for(int i = 0; i <= (slen/2)-1; i++)
	{
		(*T)[i].lchild = &((*T)[2*i+1]);
		if(2*i+2 <= slen-1)
			(*T)[i].rchild = &((*T)[2*i+2]);
	}
	
	return slen;
}

