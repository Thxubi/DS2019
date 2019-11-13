#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data {
	int id;		//序号
	int code;		//编码 
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
void INQueByHTOL(LinkQueue *Q, Data data);
void INQueByLTOH(LinkQueue *Q, Data data);
int OUTQue(LinkQueue *Q, Data *popdata);
int QueLength(LinkQueue *Q);
void FREEQue(LinkQueue *Q);
void INIT();

void apply();
void search();
void undo();

LinkQueue buy, sell;
int id = 0;

int main()
{
	int a, f1 = 1;
	INIT();
	while(f1)
	{
		scanf("%d", &a);
		switch(a)
		{
			case 1:
				apply();
				break;
			case 2:
				search();
				break;
			case 3:
				undo();
				break;
			case 0:
				f1 = 0;
				break;
		}
	}
}

void apply()
{
	Data temp;
	scanf("%d%f%d", &temp.code, &temp.price, &temp.quantity);
	scanf(" %c", &temp.bors);
	temp.id = ++id;
	printf("orderid: %04d\n", temp.id);
	if(temp.bors == 'b')
		INQueByHTOL(&buy, temp);
	else
		INQueByLTOH(&sell, temp);
}

void search()
{
	;
}

void undo()
{
	;
}

void INIT()
{
	INITQue(&buy);
	INITQue(&sell);
}

void INITQue(LinkQueue *Q)
{
	Q->front = Q->rear = (Ptr)malloc(sizeof(Node));
	Q->front->next = NULL;
}

void INQueByLTOH(LinkQueue *Q, Data data)			//in queue by low to high
{
	Ptr p, temp;
	p = (Ptr)malloc(sizeof(Node));
	//检查操作 
	p->data = data;
	p->next = NULL;
	
	temp = Q->front;
	if(temp == Q->rear || Q->rear->data.price <= p->data.price)
	{
		Q->rear->next = p;
		Q->rear = p;
	}
	else
	{
		while(temp != Q->rear)
		{
			if(p->data.price < temp->next->data.price)
			{
				p->next = temp->next;
				temp->next = p;
				break;
			}
		}
	}
}

void INQueByHTOL(LinkQueue *Q, Data data)			//in queue by high to low
{
	Ptr p, temp;
	p = (Ptr)malloc(sizeof(Node));
	//检查操作 
	p->data = data;
	p->next = NULL;
	
	temp = Q->front;
	if(temp == Q->rear || Q->rear->data.price >= p->data.price)
	{
		Q->rear->next = p;
		Q->rear = p;
	}
	else
	{
		while(temp != Q->rear)
		{
			if(p->data.price > temp->next->data.price)
			{
				p->next = temp->next;
				temp->next = p;
				break;
			}
		}
	}
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
