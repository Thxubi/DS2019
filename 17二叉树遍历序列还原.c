#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSSIZE 1000


typedef struct bitnode {
	char data;
	struct bitnode *lchild, *rchild;
} BiTNode, *BiTPtr;

typedef struct node {
	BiTPtr data;
	struct node * next;
} Node, * Ptr;

typedef struct {
	Ptr front;		//队头 
	Ptr rear;      //队尾 
} LinkQueue;


LinkQueue ls;

void INITQue(LinkQueue *Q);
void INQue(LinkQueue *Q, BiTPtr data);
int OUTQue(LinkQueue *Q, BiTPtr *popdata);
void CreateBiT(BiTPtr T, int m, int p, int length);
void output(BiTPtr T); 
char mid[MAXSSIZE+1], post[MAXSSIZE+1];

int slen;
int main()
{
	BiTNode Tree;
	gets(mid);
	gets(post);
	slen = strlen(mid);
	
	CreateBiT(&Tree, 0, 0, slen);
	
	output(&Tree);
	return 0;
}
void INITQue(LinkQueue *Q)
{
	Q->front = Q->rear = (Ptr)malloc(sizeof(Node));
	Q->front->next = NULL;
}

void INQue(LinkQueue *Q, BiTPtr data)
{
	Ptr p;
	p = (Ptr)malloc(sizeof(Node));
	//检查操作 
	p->data = data;
	p->next = NULL;
	
	Q->rear->next = p;
	Q->rear = p;
}

int OUTQue(LinkQueue *Q, BiTPtr *popdata)
{
	if(Q->front == Q->rear)
		return 0;
	Ptr p;
	BiTPtr e;
	p = Q->front->next;
	e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
	*popdata = e;
	return 1;
}

void CreateBiT(BiTPtr T, int m, int p, int length)
{
	T->data = post[p+length-1];
	T->lchild = NULL;
	T->rchild = NULL;
	 
	if(length == 1)
		return;
		
	int i;								//当前节点在mid中的位置
	for(i = m; i < m + length; i++)
		if(mid[i] == post[p+length-1])
			break;
	if(i-m > 0)
	{
		T->lchild = (BiTPtr)malloc(sizeof(BiTNode));
		CreateBiT(T->lchild, m, p, i-m);
	}
	if(length-i+m-1 > 0)
	{
		T->rchild = (BiTPtr)malloc(sizeof(BiTNode));
		CreateBiT(T->rchild, i+1, p+i-m, length-i+m-1);
	}
}

void output(BiTPtr T)
{
	INITQue(&ls);
	INQue(&ls, T);
	BiTPtr current;
	while(slen-- && ls.front != ls.rear)
	{
		OUTQue(&ls, &current);
		printf("%c", current->data);
		if(current->lchild != NULL)
			INQue(&ls, current->lchild);
		if(current->rchild != NULL)
			INQue(&ls, current->rchild);
	}
	printf("\n");
}
