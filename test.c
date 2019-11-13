#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data {
	int num;		//编码
	float price;	//价格
	int quantity;	//数量
	char bors;		//B/S
} Data;

typedef struct node {
	Data data;
	struct node * next;
} Node, * Ptr;

typedef struct {
	Ptr front;
	Ptr rear; 
} LinkQueue;

void INITQue(LinkQueue *Q);
void INQue(LinkQueue *Q, Data data);
int OUTQue(LinkQueue *Q, Data *popdata);
int QueLength(LinkQueue *Q);
void FREEQue(LinkQueue *Q);

LinkQueue test;

int main()
{
	INITQue(&test);
	Data a;
	a.bors = 'B';
	a.num = 1;
	a.price = 0;
	a.quantity = 10;
	
	INQue(&test, a);
	Data b;
	OUTQue(&test, &b);
	printf("%c\n", b.bors);
}



void INITQue(LinkQueue *Q)
{
	Q->front = Q->rear = (Ptr)malloc(sizeof(Node));
	Q->front->next = NULL;
}

void INQue(LinkQueue *Q, Data data)
{
	Ptr p;
	p = (Ptr)malloc(sizeof(Node));
	//检查操作
	p->data = data;
	p->next = NULL;
	
	Q->rear->next = p;
	Q->rear = p;
}

int OUTQue(LinkQueue *Q, Data *popdata)
{
	if(Q->front == Q->rear) return 0;
	Ptr p;
	Data e;
	p = Q->front->next;
	e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
	*popdata = e;
	return 1;
}

int QueLength(LinkQueue *Q)
{
	int i = 0;
	Ptr p;
	p = Q->front;
	for(i = 0; p != Q->rear; i++)
	{
		p = p->next;
	}
	return i;
}

void FREEQue(LinkQueue *Q)
{
	Ptr temp;
	while(Q->front != Q->rear)
	{
		temp = Q->front;
		Q->front = Q->front->next;
		free(temp);
	}
	free(Q->front);
}
