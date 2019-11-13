#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct qnode {
	int data;
	struct qnode * next;
} QNode, * QPtr;

typedef struct {
	QPtr front;		//队头 
	QPtr rear;      //队尾 
} * LinkQueue;


void INITQue(LinkQueue Q)
{
	Q->front = Q->rear = (QPtr)malloc(sizeof(QNode));
	Q->front->next = NULL;
}

void INQue(LinkQueue Q, int num)
{
	QPtr p;
	p = (QPtr)malloc(sizeof(QNode));
	//检查操作 
	p->data = num;
	p->next = NULL;
	
	Q->rear->next = p;
	Q->rear = p;
	
}

int OUTQue(LinkQueue Q, int *popdata)
{
	if(Q->front == Q->rear) return 0;
	QPtr p;
	int e;
	p = Q->front->next;
	e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
	*popdata = e;
	return 1;
}

int QueLength(LinkQueue Q)
{
	int i = 0;
	QPtr p;
	p = Q->front;
	for(i = 0; p != Q->rear; i++)
	{
		p = p->next;
	}
	return i;
}

int main()
{
	LinkQueue a;
	INITQue(a);
}
