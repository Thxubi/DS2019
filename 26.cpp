#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define MAXVNUM 100


typedef struct arcnode
{
    int i;
    struct arcnode * ilink;
} ArcNode, *ArcPtr;

typedef struct vnode
{
    int data;
    ArcPtr firstarc;
    bool visited;
} VNode, *VPtr;
typedef struct 
{
    VNode vnode[MAXVNUM];
    int vnum, arcnum;
} Graph;

void bfs(Graph *G, VPtr p);
int another(ArcPtr arc, int v);

int main()
{
    Graph G;
    scanf("%d", &G.vnum);
    G.arcnum = 0;

    for (int i = 0; i < G.vnum; i++)
    {
        G.vnode[i].data = i;
        G.vnode[i].firstarc = NULL;
        G.vnode[i].visited = false;
    }

    int i, j;
    for (scanf("%d", &i); i != -1; scanf("%d", &i))
    {
        scanf("%d", &j);
        G.arcnum ++;
        
        ArcPtr temparc;
        temparc = (ArcPtr)malloc(sizeof(ArcNode));

        temparc->i = j;
        temparc->ilink = NULL;

        if (G.vnode[i].firstarc == NULL)
        {
            G.vnode[i].firstarc = temparc;
        }
        else
        {
            ArcPtr bftemp = G.vnode[i].firstarc;
            
            if (bftemp->i > j)
            {
                temparc->ilink= G.vnode[i].firstarc;
                G.vnode[i].firstarc = temparc;
            }
            else
            {
                for (bftemp; bftemp != NULL; bftemp = bftemp->ilink)
                {
                    if (bftemp->ilink == NULL || bftemp->ilink->i > j)
                    {
                        temparc->ilink = bftemp->ilink;
                        bftemp->ilink = temparc;
                        break;
                    }
                }
            }
        }
        
        temparc = (ArcPtr)malloc(sizeof(ArcNode));

        temparc->i = i;
        temparc->ilink = NULL;

        if (G.vnode[j].firstarc == NULL)
        {
            G.vnode[j].firstarc = temparc;
        }
        else
        {
            ArcPtr bftemp = G.vnode[j].firstarc;
            
            if (bftemp->i > i)
            {
                temparc->ilink= G.vnode[j].firstarc;
                G.vnode[j].firstarc = temparc;
            }
            else
            {
                for (bftemp; bftemp != NULL; bftemp = bftemp->ilink)
                {
                    if (bftemp->ilink == NULL || bftemp->ilink->i > i)
                    {
                        temparc->ilink = bftemp->ilink;
                        bftemp->ilink = temparc;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < G.vnum; i++)
    {
        if (!G.vnode[i].visited)
        {
            bfs(&G, &G.vnode[i]);
            printf("\n");
        }
        
    }
    
    return 0;
}

void bfs(Graph *G, VPtr p)
{
    queue <int> q;
    printf("%d", p->data);
    p->visited = true;

    for (ArcPtr temp = p->firstarc; temp != NULL;)
    {
            if (G->vnode[temp->i].visited)
            {
                temp = temp->ilink;
                continue;
            }
            
            q.push(temp->i);
            G->vnode[temp->i].visited = true;
            temp = temp->ilink;
    }
    
    while(!q.empty())
    {
        int current;
        current = q.front();
        printf("-%d", current);
        q.pop();
        
        for (ArcPtr temp = G->vnode[current].firstarc; temp != NULL;)
        {
                if (G->vnode[temp->i].visited)
                {
                    temp = temp->ilink;
                    continue;
                }
                
                q.push(temp->i);
                G->vnode[temp->i].visited = true;
                temp = temp->ilink;
        }
    }
}