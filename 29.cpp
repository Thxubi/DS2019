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
    char data;
    struct bitnode *lchild, *rchild;
    int height;
    int degree;
} BiTNode, *BiTPtr;

stack<BiTPtr> S;

void INITBiTNode(BiTPtr p);
void getdegree(BiTPtr root);
BiTPtr InsertAVL(BiTPtr root, char data);
void PrintTab(int n);
void ins_tab(BiTPtr T);
void ins(BiTPtr T);
void pres(BiTPtr T);
void posts(BiTPtr T);
int height(BiTPtr p);
int max(int a, int b);
BiTPtr LeftRotate(BiTPtr p);  //左单旋(RH)
BiTPtr RightRotate(BiTPtr p); //右单旋
BiTPtr LR(BiTPtr p);
BiTPtr RL(BiTPtr p);

int main()
{
    BiTPtr root = NULL;

    char data = getchar();
    while (data != '\n')
    {
        root = InsertAVL(root, data);
        data = getchar();
    }

    printf("Preorder: ");
    pres(root);
    printf("\nInorder: ");
    ins(root);
    printf("\nPostorder: ");
    posts(root);
    printf("\nTree:\n");
    getdegree(root);
    ins_tab(root);

    while (!S.empty())
    {
        PrintTab(S.top()->degree);
        printf("%c\n", S.top()->data);
        S.pop();
    }

    return 0;
}

BiTPtr LeftRotate(BiTPtr p)
{
    BiTPtr rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p->height = max(height(p->lchild), height(p->rchild)) + 1;
    rc->height = max(height(rc->lchild), height(rc->rchild)) + 1;

    return rc;
}
BiTPtr RightRotate(BiTPtr p)
{
    BiTPtr lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p->height = max(height(p->lchild), height(p->rchild)) + 1;
    lc->height = max(height(lc->lchild), height(lc->rchild)) + 1;

    return lc;
}
BiTPtr LR(BiTPtr p)
{
    p->lchild = LeftRotate(p->lchild);
    return RightRotate(p);
}
BiTPtr RL(BiTPtr p)
{
    p->rchild = RightRotate(p->rchild);
    return LeftRotate(p);
}

void INITBiTNode(BiTPtr p)
{
    p->data = 0;
    p->lchild = p->rchild = NULL;
    p->degree = 0;
    p->height = 0;
}
int height(BiTPtr p)
{
    if (p == NULL)
    {
        return -1;
    }
    else
    {
        return p->height;
    }
}
int max(int a, int b)
{
    return a > b ? a : b;
}

BiTPtr InsertAVL(BiTPtr root, char data)
{

    if (root == NULL)
    {
        root = (BiTPtr)malloc(sizeof(BiTNode));
        INITBiTNode(root);
        root->data = data;
    }
    else if (data < root->data)
    {
        root->lchild = InsertAVL(root->lchild, data);
        if (height(root->lchild) - height(root->rchild) == 2)
        {
            if (data < root->lchild->data)
            {
                root = RightRotate(root);
            }
            else
            {
                root = LR(root);
            }
        }
    }
    else if (data > root->data)
    {
        root->rchild = InsertAVL(root->rchild, data);
        if (height(root->rchild) - height(root->lchild) == 2)
        {
            if (data > root->rchild->data)
            {
                root = LeftRotate(root);
            }
            else
            {
                root = RL(root);
            }
        }
    }
    root->height = max(height(root->lchild), height(root->rchild)) + 1;
    return root;
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
    if (T != NULL)
    {
        ins_tab(T->lchild);
        S.push(T);
        ins_tab(T->rchild);
    }
    else
    {
        return;
    }
}

void ins(BiTPtr T)
{
    if (T == NULL)
        return;
    else
    {
        ins(T->lchild);
        printf("%c", T->data);
        ins(T->rchild);
    }
}
void pres(BiTPtr T)
{
    if (T == NULL)
        return;
    else
    {
        printf("%c", T->data);
        pres(T->lchild);
        pres(T->rchild);
    }
}
void posts(BiTPtr T)
{
    if (T == NULL)
        return;
    else
    {
        posts(T->lchild);
        posts(T->rchild);
        printf("%c", T->data);
    }
}

void getdegree(BiTPtr p)
{
    int d = p->degree + 1;
    if (p->lchild)
    {
        p->lchild->degree = d;
        getdegree(p->lchild);
    }
    if (p->rchild)
    {
        p->rchild->degree = d;
        getdegree(p->rchild);
    }
}