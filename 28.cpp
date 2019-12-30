#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef struct bitnode
{
    int data;
    struct bitnode *lchild, *rchild;
    int degree;
} BiTNode, *BiTPtr;

void INITBiTNode(BiTPtr p);
void CreateBST(BiTPtr root);
bool SearchBST(BiTPtr root, int key, BiTPtr f, BiTPtr p);
void InsertBST(BiTPtr root, int data);
void PrintTab(int n);
void ins_tab(BiTPtr T);
void ins(BiTPtr T);

int main()
{
    BiTNode root;
    INITBiTNode(&root);

    CreateBST(&root);

    ins_tab(&root);
    printf("\n");
    ins(&root);
    printf("\n");
    return 0;
}

void INITBiTNode(BiTPtr p)
{
    p->data = 0;
    p->lchild = p->rchild = NULL;
    p->degree = 0;
}

void CreateBST(BiTPtr root)
{
    int data;
    scanf("%d", &data);
    getchar();
    while (data)
    {
        InsertBST(root, data);
        scanf("%d", &data);
    }
}
bool SearchBST(BiTPtr root, int key, BiTPtr f, BiTPtr *p)
{
    if (!root || root->data == 0)
    {
        *p = f;
        return false;
    }
    else if (key == root->data)
    {
        *p = root;
        return true;
    }
    else if (key < root->data)
    {
        return SearchBST(root->lchild, key, root, p);
    }
    else
    {
        return SearchBST(root->rchild, key, root, p);
    }
}
void InsertBST(BiTPtr root, int data)
{
    BiTPtr p;
    if (!SearchBST(root, data, NULL, &p))
    {
        BiTPtr current = (BiTPtr)malloc(sizeof(BiTNode));
        INITBiTNode(current);
        current->data = data;
        if (p == NULL)
        {
            root->data = current->data;
            root->degree = 0;
        }
        else if (current->data < p->data)
        {
            current->degree = p->degree + 1;
            p->lchild = current;
        }
        else
        {
            current->degree = p->degree + 1;
            p->rchild = current;
        }
    }
}

void PrintTab(int n)
{
    for (int i = n; i != 0; i--)
    {
        printf("    ");
    }
}

void ins_tab(BiTPtr T)
{
    if (T == NULL)
        return;
    else
    {
        ins_tab(T->lchild);
        PrintTab(T->degree);
        printf("%d\n", T->data);
        ins_tab(T->rchild);
    }
}

void ins(BiTPtr T)
{
    if (T == NULL)
        return;
    else
    {
        ins(T->lchild);
        printf(" %d", T->data);
        ins(T->rchild);
    }
}