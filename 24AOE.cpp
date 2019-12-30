#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define MAXVNUM 1000
#define MAXDATALENGTH 10

typedef struct arcnode
{               // 弧
    int value;  // 权值
    int adjvex; // 依附的节点
    struct arcnode *nextarc;
    bool keypath;
} ArcNode, *ArcPtr;

typedef struct vnode
{
    int num;
    char data[MAXDATALENGTH];
    ArcPtr firstarc;
} VNode, VList[MAXVNUM];

typedef struct
{
    VList vlist;
    int vnum, arcnum;
} ALGraph;

struct cmp1
{
    bool operator()(VNode a, VNode b)
    {
        return a.num > b.num;
    }
};

typedef struct mystack
{
    int num;
    struct mystack *before, *next;

} MyStack, *MSPtr;

void CreateAOE(ALGraph *G);
void GetIndegree(ALGraph *G, int *indgree);
void TPSort(ALGraph *G);
void INStack(ALGraph *G, MSPtr s);
void PrintStack(ALGraph *G, MSPtr base);

int main()
{
    ALGraph G;
    CreateAOE(&G);
    TPSort(&G);
    return 0;
}

void CreateAOE(ALGraph *G)
{
    scanf("%d,%d", &(G->vnum), &(G->arcnum));
    getchar();

    for (int i = 0; i < G->vnum; i++)
    {
        G->vlist[i].firstarc = NULL;
        G->vlist[i].num = i;
        int tempi = 0;
        for (char tempc = getchar(); tempc != ',' && tempc != '\n'; tempc = getchar())
        {
            G->vlist[i].data[tempi++] = tempc;
        }
        G->vlist[i].data[tempi] = '\0';
    }

    for (int i = 0; i < G->arcnum; i++)
    {
        int start, end, value;
        scanf("<%d,%d,%d>", &start, &end, &value);
        ArcPtr temp = (ArcPtr)malloc(sizeof(ArcNode));
        temp->adjvex = end;
        temp->nextarc = NULL;
        temp->value = value;
        temp->keypath = false;

        // temp->nextarc = G->vlist[start].firstarc;
        // G->vlist[start].firstarc = temp;

        if (G->vlist[start].firstarc == NULL)
        {
            G->vlist[start].firstarc = temp;
        }
        else
        {
            ArcPtr bftemp = G->vlist[start].firstarc;
            if (bftemp->adjvex > temp->adjvex)
            {
                temp->nextarc = bftemp;
                G->vlist[start].firstarc = temp;
            }
            else
            {
                for (bftemp; bftemp != NULL; bftemp = bftemp->nextarc)
                {
                    if (bftemp->nextarc == NULL || bftemp->nextarc->adjvex > temp->adjvex)
                    {
                        temp->nextarc = bftemp->nextarc;
                        bftemp->nextarc = temp;
                        break;
                    }
                }
            }
        }
        getchar();
    }
}

void GetIndegree(ALGraph *G, int *indgree)
{
    for (int i = 0; i < G->vnum; i++)
    {
        for (ArcPtr temp = G->vlist[i].firstarc; temp != NULL; temp = temp->nextarc)
        {
            indgree[temp->adjvex]++;
        }
    }
}

void TPSort(ALGraph *G)
{
    priority_queue<VNode, vector<VNode>, cmp1> pq;
    stack<int> S;
    int topo[MAXVNUM] = {0};
    int ve[MAXVNUM] = {0};
    int vl[MAXVNUM] = {0};

    int indegree[MAXVNUM] = {0};
    GetIndegree(G, indegree);

    for (int i = 0; i < G->vnum; i++)
    {
        if (indegree[i] == 0)
        {
            pq.push(G->vlist[i]);
        }
    }

    int count = 0;
    while (!pq.empty())
    {
        int current = pq.top().num;
        topo[count++] = pq.top().num;
        pq.pop();
        S.push(current);
        for (ArcPtr p = G->vlist[current].firstarc; p != NULL; p = p->nextarc)
        {
            indegree[p->adjvex]--;
            if (indegree[p->adjvex] == 0)
            {
                pq.push(G->vlist[p->adjvex]);
            }
            if (ve[current] + p->value > ve[p->adjvex])
            {
                ve[p->adjvex] = ve[current] + p->value;
            }
        }
    }
    if (count == G->vnum)
    {
        for (int i = 0; i < count; i++)
        { //输出拓扑序列
            int j = 0;
            while (G->vlist[topo[i]].data[j] != '\0')
            {
                putchar(G->vlist[topo[i]].data[j++]);
            }
            if (i != count - 1)
                printf("-");
            else
                printf("\n");
        }

        while (!S.empty())
        { //求得vl
            int current = S.top();
            vl[current] = ve[G->vnum - 1];
            S.pop();

            for (ArcPtr p = G->vlist[current].firstarc; p != NULL; p = p->nextarc)
            {
                if (vl[p->adjvex] - p->value < vl[current])
                {
                    vl[current] = vl[p->adjvex] - p->value;
                }
            }
        }

        for (int i = 0; i < G->vnum; i++)
        { //存入关键路径
            for (ArcPtr p = G->vlist[topo[i]].firstarc; p != NULL; p = p->nextarc)
            {
                int ee = ve[topo[i]];
                int el = vl[p->adjvex] - p->value;
                if (ee == el)
                {
                    p->keypath = true;
                    //printf("%s %s\n", G->vlist[topo[i]].data, G->vlist[p->adjvex].data);
                }
            }
        }

        for (int i = 0; i < G->vnum; i++)
        {
            ArcPtr current = G->vlist[i].firstarc;
            for (current; current != NULL && current->keypath != true; current = current->nextarc)
                ;
            G->vlist[i].firstarc = current;

            if (current != NULL)
            {
                for (ArcPtr p = current->nextarc; p != NULL; p = p->nextarc)
                {
                    if (p->keypath)
                    {
                        current->nextarc = p;
                        current = p;
                    }
                }

                current->nextarc = NULL;
            }
        }

        MSPtr base;
        base = (MSPtr)malloc(sizeof(MyStack));
        base->num = 0;
        base->next = NULL;
        base->before = NULL;

        INStack(G, base);
    }
    else
    {
        printf("NO TOPOLOGICAL PATH\n");
    }
}

void INStack(ALGraph *G, MSPtr s)
{
    if (G->vlist[s->num].firstarc == NULL)
    { //结束
        PrintStack(G, s);
    }

    else
    {
        ArcPtr current = G->vlist[s->num].firstarc;
        for (current; current != NULL; current = current->nextarc)
        {
            MSPtr temp;
            temp = (MSPtr)malloc(sizeof(MyStack));
            temp->num = current->adjvex;
            temp->next = NULL;
            temp->before = s;
            s->next = temp;

            INStack(G, temp);
        }
    }
}

void PrintStack(ALGraph *G, MSPtr top)
{
    MSPtr tempms;
    for (tempms = top; tempms->before != NULL; tempms = tempms->before)
        ;
    for (tempms; tempms != NULL; tempms = tempms->next)
    { // 输出整条路径
        int j = 0;
        while (G->vlist[tempms->num].data[j] != '\0')
        {
            putchar(G->vlist[tempms->num].data[j++]);
        }
        if (tempms->next != NULL)
            printf("-");
        else
            printf("\n");
    }
}