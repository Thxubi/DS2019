#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef struct
{
    int key;
    int data;
} SSElem, *SSElemPtr;

typedef struct
{
    SSElemPtr elem;
    int length;
} SSTable;

int cmp(const void *a, const void *b)
{
    SSElemPtr aa = (SSElemPtr)a;
    SSElemPtr bb = (SSElemPtr)b;
    return aa->key > bb->key;
}

void SSInput(SSTable *SS);
void ShowAll(SSTable *SS);
int SSSearch(SSTable *SS, int key);
int main()
{
    SSTable SS;
    scanf("%d", &SS.length);

    SSInput(&SS);
    ShowAll(&SS);

    int i, ans;
    scanf("%d", &i);

    ans = SSSearch(&SS, i);
    if (ans == -1)
    {
        printf("error\n");
    }
    else
    {
        printf("(%d %d)\n", SS.elem[ans].key, SS.elem[ans].data);
    }

    return 0;
}

void SSInput(SSTable *SS)
{
    SS->elem = (SSElemPtr)malloc(sizeof(SSElem) * SS->length);
    for (int i = 0; i < SS->length; i++)
    {
        scanf("%d%d", &SS->elem[i].key, &SS->elem[i].data);
    }
    qsort(SS->elem, SS->length, sizeof(SS->elem[0]), cmp);
}

void ShowAll(SSTable *SS)
{
    for (int i = 0; i < SS->length; i++)
    {
        printf("(%d %d)", SS->elem[i].key, SS->elem[i].data);
    }
    printf("\n");
}

int SSSearch(SSTable *SS, int key)
{
    int low = 0, high = SS->length - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (SS->elem[mid].key == key)
        {
            return mid;
        }
        else
        {
            if (SS->elem[mid].key > key)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
    }
    return -1;
}