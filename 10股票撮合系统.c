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
	{
		Ptr current = sell.front;
		while(current != sell.rear)
		{
			current = current->next;
			if(current->data.quantity == 0)
				continue;
			if(current->data.code == temp.code && current->data.price <= temp.price)
			{
				int qu;
				if(current->data.quantity >= temp.quantity)
				{
					qu = temp.quantity;
					current->data.quantity -= qu;
					temp.quantity = 0;
				}
				else
				{
					qu = current->data.quantity;
					current->data.quantity = 0;
					temp.quantity -= qu;
				}
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (temp.price+current->data.price)/2, qu, temp.id, current->data.id);
				if(temp.quantity == 0) break;
			}
		}
		if(temp.quantity != 0)
			INQueByHTOL(&buy, temp);
	}
	else
	{
		Ptr current = buy.front;
		while(current != buy.rear)
		{
			current = current->next;
			if(current->data.quantity == 0)
				continue;
			if(current->data.code == temp.code && current->data.price >= temp.price)
			{
				int qu;
				if(current->data.quantity >= temp.quantity)
				{
					qu = temp.quantity;
					current->data.quantity -= qu;
					temp.quantity = 0;
				}
				else
				{
					qu = current->data.quantity;
					current->data.quantity = 0;
					temp.quantity -= qu;
				}
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (temp.price+current->data.price)/2, qu, temp.id, current->data.id);
				if(temp.quantity == 0) break;
			}
		}
		if(temp.quantity != 0)
			INQueByLTOH(&sell, temp);
	}
}

void search()
{
	int scode;
	Ptr current;
	scanf("%d", &scode);
	printf("buy orders:\n");
	for(current = buy.front; current != buy.rear;)
	{
		current = current->next;
		if(current->data.code == scode && current->data.quantity != 0)
			printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", current->data.id, current->data.code, current->data.price, current->data.quantity, current->data.bors);
	}
	printf("sell orders:\n");
	for(current = sell.front; current != sell.rear;)
	{
		current = current->next;
		if(current->data.code == scode && current->data.quantity != 0)
			printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", current->data.id, current->data.code, current->data.price, current->data.quantity, current->data.bors);
	}
}

void undo()
{
	int uid, flag = 1;
	scanf("%d", &uid);
	Ptr current;
	for(current = buy.front; current != buy.rear;)
	{
		current = current->next;
		if(current->data.id == uid && current->data.quantity != 0)
		{
			printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", current->data.id, current->data.code, current->data.price, current->data.quantity, current->data.bors);
			current->data.quantity = 0;
			flag = 0;
			break;
		}
	}
	if(flag)
		for(current = sell.front; current != sell.rear;)
		{
			current = current->next;
			if(current->data.id == uid && current->data.quantity != 0)
			{
				printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", current->data.id, current->data.code, current->data.price, current->data.quantity, current->data.bors);
				current->data.quantity = 0;
				flag = 0;
				break;
			}
		}
	
	if(flag)
		printf("not found\n");
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
			temp = temp->next;
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
			temp = temp->next;
		}
	}
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
