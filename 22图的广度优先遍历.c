#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXVNUM 100

typedef struct arcnode {
	int vnodenum;
	struct arcnode *nextarc;
} ArcNode;

typedef struct vnode {
	char data;
	ArcNode *firstarc;
} VNode, VList[MAXVNUM+1];

typedef struct {
	VList graph;
	int vnum, arcnum;
	int kind;
} ALGraph;

typedef struct node {
	VNode data;
	struct node * next;
} Node, * Ptr;

typedef struct {
	Ptr front;		//队头 
	Ptr rear;      //队尾 
} LinkQueue;

void INITQue(LinkQueue *Q);
void INQue(LinkQueue *Q, VNode data);
int OUTQue(LinkQueue *Q, VNode *popdata);
void CreateGraph(ALGraph* G);
void PrintGraph(ALGraph* G);
void bfs(ALGraph* G);

int main()
{
	ALGraph G;
	CreateGraph(&G);
	PrintGraph(&G);
	bfs(&G);
	
	return 0;
}

void CreateGraph(ALGraph* G)
{
	char tempc;
	int vnum = 0;
	for(tempc = getchar(); tempc != '*'; tempc = getchar())
	{
		G->graph[vnum++].data = tempc;
		G->graph[vnum-1].firstarc = NULL;
		getchar();
	}
	getchar();
	
	G->vnum = vnum;
	
	int a, b, arcnum;
	scanf("%d,%d", &a, &b);
	for(arcnum = 1; a != -1 && b != -1; arcnum++)
	{
		ArcNode *tempvn;
		
		tempvn = (ArcNode*)malloc(sizeof(ArcNode));
		tempvn->vnodenum = b;
		tempvn->nextarc = NULL;
		
		if(G->graph[a].firstarc == NULL)
			G->graph[a].firstarc = tempvn;
		else
		{
			tempvn->nextarc = G->graph[a].firstarc;
			G->graph[a].firstarc = tempvn;
		}
		
		tempvn = (ArcNode*)malloc(sizeof(ArcNode));
		tempvn->vnodenum = a;
		tempvn->nextarc = NULL;
		
		if(G->graph[b].firstarc == NULL)
			G->graph[b].firstarc = tempvn;
		else
		{
			tempvn->nextarc = G->graph[b].firstarc;
			G->graph[b].firstarc = tempvn;
		}
			
		scanf("%d,%d", &a, &b);
	}
	G->arcnum = arcnum - 1;
}
void PrintGraph(ALGraph* G)
{
	printf("the ALGraph is\n");
	for(int i = 0; i < G->vnum; i++)
	{
		printf("%c", G->graph[i].data);
		ArcNode* tempvn;
		for(tempvn = G->graph[i].firstarc; tempvn != NULL; tempvn = tempvn->nextarc)
			printf(" %d", tempvn->vnodenum);
		printf("\n");
	}
}
void bfs(ALGraph* G)
{
	printf("the Breadth-First-Seacrh list:");
	int visited[MAXVNUM+1] = {0};
	LinkQueue Q;
	INITQue(&Q);
	
	for(int i = 0; i < G->vnum; i++)
	{
		if(visited[i] == 0)
		{
			visited[i] = 1;
			printf("%c", G->graph[i].data);
			INQue(&Q, G->graph[i]);
			while(Q.front != Q.rear)
			{
				VNode tempvn;
				ArcNode* temparc;
				OUTQue(&Q, &tempvn);
				for(temparc = tempvn.firstarc; temparc != NULL; temparc = temparc->nextarc)
				{
					if(visited[temparc->vnodenum] == 0)
					{
						visited[temparc->vnodenum] = 1;
						printf("%c", G->graph[temparc->vnodenum].data);
						INQue(&Q, G->graph[temparc->vnodenum]);
					}
				}
			}
		}
	}
	printf("\n");
	return;
}
void INITQue(LinkQueue *Q)
{
	Q->front = Q->rear = (Ptr)malloc(sizeof(Node));
	Q->front->next = NULL;
}
void INQue(LinkQueue *Q, VNode data)
{
	Ptr p;
	p = (Ptr)malloc(sizeof(Node));
	//检查操作 
	p->data = data;
	p->next = NULL;
	
	Q->rear->next = p;
	Q->rear = p;
}
int OUTQue(LinkQueue *Q, VNode *popdata)
{
	if(Q->front == Q->rear) return 0;
	Ptr p;
	VNode e;
	p = Q->front->next;
	e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
	*popdata = e;
	return 1;
}
