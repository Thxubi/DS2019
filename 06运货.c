#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	struct node * next;
} Node, * Ptr;

typedef struct {
	Ptr front;		//队头 
	Ptr rear;      //队尾 
} LinkQueue;

typedef struct {
	Ptr top;
	Ptr base;
} LinkStack;


void INITQue(LinkQueue *Q);
void INQue(LinkQueue *Q, int data);
int OUTQue(LinkQueue *Q, int *popdata);
int QueLength(LinkQueue *Q);
void FREEQue(LinkQueue *Q);
void INITStack(LinkStack *S);
void INStack(LinkStack *S, int data);
int OUTStack(LinkStack *S, int *popdata);
void FREEStack(LinkStack *S);

void INITALL(int n);
void FREEALL(int n);


void sim(int i);
int check();

LinkQueue bplat[101];
LinkStack truck;

int n, s, q;
long long int sumtime;
int t_num;
int main()
{
	int set;
	scanf("%d", &set);
	while(set--)
	{
		scanf("%d%d%d", &n, &s, &q);
		INITALL(n);
		//first
		for(int i = 1; i <= n; i++)
		{
			int temp, innum;
			scanf("%d", &innum);
			for(int j = 0; j < innum; j++)
			{
				scanf("%d", &temp);
				INQue(&bplat[i], temp);
			}
			sim(i);
		}
		//others
		while(check() == 0)
		{
			for(int i = 1; i <= n; i++)
			{
				if(check() == 1) break;			
				sim(i);
			}
		}
		printf("%lld\n", sumtime);
		FREEALL(n);
	}
}

int check()
{
	for(int i = 1; i <= n; i++)
	{
		if(QueLength(&bplat[i]) == 0)
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	if(t_num == 0)
		return 1;
	else
		return 0;
}

void sim(int i)
{
	sumtime += 2;
	int temp;
	// out from truck
	while(t_num != 0)
	{
		if(truck.top->data == i)
		{
			OUTStack(&truck, &temp);
			sumtime ++;
			t_num --;
			continue;
		}
		else
		{
			if(QueLength(&bplat[i]) == q)
				break;
			else
			{
				OUTStack(&truck, &temp);
				INQue(&bplat[i], temp);
				sumtime++;
				t_num--;
			}
		}
	}
	// load in truck
	while(t_num < s && QueLength(&bplat[i]) > 0)
	{
		OUTQue(&bplat[i], &temp);
		INStack(&truck, temp);
		sumtime++;
		t_num++;
	}
}

void INITALL(int n)
{
	INITStack(&truck);
	for(int i = 0; i <= n; i++)
		INITQue(&bplat[i]);
	sumtime = -2;
	t_num = 0;
}

void FREEALL(int n)
{
	FREEStack(&truck);
	for(int i = 0; i <= n; i++)
		FREEQue(&bplat[i]);
}
void INITQue(LinkQueue *Q)
{
	Q->front = Q->rear = (Ptr)malloc(sizeof(Node));
	Q->front->next = NULL;
}

void INQue(LinkQueue *Q, int data)
{
	Ptr p;
	p = (Ptr)malloc(sizeof(Node));
	//检查操作 
	p->data = data;
	p->next = NULL;
	
	Q->rear->next = p;
	Q->rear = p;
}

int OUTQue(LinkQueue *Q, int *popdata)
{
	if(Q->front == Q->rear) return 0;
	Ptr p;
	int e;
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

void INITStack(LinkStack *S)
{
	S->base = S->top = (Ptr)malloc(sizeof(Node));
	S->base->next = NULL;
}

void INStack(LinkStack *S, int data)
{
	Ptr p;
	p = (Ptr)malloc(sizeof(Node));
	//检查操作 
	p->data = data;
	p->next = S->top;
	
	S->top = p;
}

int OUTStack(LinkStack *S, int *popdata)
{
	if(S->base == S->top) return 0;
	Ptr p;
	int e;
	p = S->top;
	e = p->data;
	S->top = p->next;
	free(p);
	*popdata = e;
	return 1;
}

void FREEStack(LinkStack *S)
{
	Ptr temp;
	while(S->top != S->base)
	{
		temp = S->top;
		S->top = temp->next;
		free(temp);
	}
	free(S->base);
}
