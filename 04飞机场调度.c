#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RW 20

typedef struct qnode {
	int data;
	struct qnode * next;
} QNode, * QPtr;

typedef struct {
	QPtr front;		//队头 
	QPtr rear;      //队尾 
} LinkQueue;

void INITQue(LinkQueue *Q);
void INQue(LinkQueue *Q, int num);
int OUTQue(LinkQueue *Q, int *popdata);
int QueLength(LinkQueue *Q);

LinkQueue downpl, uppl;

int main()
{
	int rwnumber, downtime, uptime;
	scanf("%d%d%d", &rwnumber, &downtime, &uptime);
	
	INITQue(&downpl);
	INITQue(&uppl);
	
	int sumtime, dnum = 5000, unum = 0, dwait = 0, uwait = 0, dmax = 0, umax = 0;
	int runway[MAX_RW][3] = {0};
	
	int flag = 1;
	for(sumtime = 0; ; sumtime ++)
	{
		printf("Current Time: %4d\n", sumtime);
		
		for(int i=1; i <= rwnumber; i++)
		{
			if(((runway[i][0] <= 5000) && (runway[i][1] == uptime))||((runway[i][0] > 5000) && (runway[i][1] == downtime)))
			{
				printf("runway %02d is free\n", i);
				runway[i][1] = 0;
				runway[i][0] = 0;
			}
		}
		
		int downpl_num = 0, uppl_num = 0;
		if(flag)
		{
			scanf("%d%d", &downpl_num, &uppl_num);
			if(downpl_num == -1 && uppl_num == -1)
			{
				downpl_num = 0;
				uppl_num = 0;
				flag = 0;
			}
		}
		dmax += downpl_num;
		umax += uppl_num;
		
		for(int i=1; i <= downpl_num; i++)
		{
			dnum ++;
			INQue(&downpl, dnum);
		}
		for(int i=1; i <= uppl_num; i++)
		{
			unum ++;
			INQue(&uppl, unum);
		}
		
		for(int i = 1; i <= rwnumber; i++)
		{
			if(runway[i][0] != 0)
			{
				runway[i][1] ++;
				runway[i][2] ++;
			}
			if(runway[i][0] == 0)
			{
				
				if(downpl.front != downpl.rear)
				{
					OUTQue(&downpl, &runway[i][0]);
					printf("airplane %04d is ready to land on runway %02d\n", runway[i][0], i);
					runway[i][1]++;
					runway[i][2]++;
				}
				else if(uppl.front != uppl.rear)
				{
					OUTQue(&uppl, &runway[i][0]);
					printf("airplane %04d is ready to takeoff on runway %02d\n", runway[i][0], i);
					runway[i][1]++;
					runway[i][2]++;
				}
			}
		}
		
		dwait += QueLength(&downpl);
		uwait += QueLength(&uppl);
		
		int fflag = 1;
		if(flag == 0)
		{
			for(int i = 1; i <= rwnumber; i++)
			{
				if(runway[i][0] != 0)
				{
					fflag = 0;
					break;
				}
			}
			if(fflag) break;
		}
	}
	
	printf("simulation finished\nsimulation time: %4d\n", sumtime);
	printf("average waiting time of landing: %4.1f\n", (float)dwait/(float)dmax);
	printf("average waiting time of takeoff: %4.1f\n", (float)uwait/(float)umax);
	float all_busy_time = 0;
	for(int i = 1; i <= rwnumber; i++)
	{
		printf("runway %02d busy time: %4d\n", i, runway[i][2]);
		all_busy_time += runway[i][2];
	}
	printf("runway average busy time percentage: %4.1f%%\n", (all_busy_time/rwnumber)*100/sumtime);
}

void INITQue(LinkQueue *Q)
{
	Q->front = Q->rear = (QPtr)malloc(sizeof(QNode));
	Q->front->next = NULL;
}

void INQue(LinkQueue *Q, int num)
{
	QPtr p;
	p = (QPtr)malloc(sizeof(QNode));
	
	//检查操作 
	
	p->data = num;
	p->next = NULL;
	
	Q->rear->next = p;
	Q->rear = p;
	
}

int OUTQue(LinkQueue *Q, int *popdata)
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

int QueLength(LinkQueue *Q)
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
