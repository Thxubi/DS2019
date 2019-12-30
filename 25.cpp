#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define MAXNAMELENGTH 21

typedef struct tnode
{
    char name[MAXNAMELENGTH];
    struct tnode *firstchild, *rightbrother, *father;
    int degree;
} TNode, *TPtr;

TPtr FindPerson(TPtr T, char* name);
void INITTNode(TPtr T);
void PrintTree(TPtr T);
void Printplus(TPtr T);
void UPTNode(TPtr T);

int main()
{
    char str1[MAXNAMELENGTH];
    char str2[MAXNAMELENGTH];
    char str3[MAXNAMELENGTH];

    TNode root;
    INITTNode(&root);
    fgets(str1, MAXNAMELENGTH, stdin);
    if (str1[strlen(str1) - 1] == '\n')
        str1[strlen(str1) - 1] = '\0';
    strcpy(root.name, str1);

    while (scanf("%s", str1) != EOF)
    {
        if (!strcmp(str1, "fire"))      //fffffffffffffffffffire
        {
            getchar();
            scanf("%s", str2);
            getchar();

            TPtr fireman = FindPerson(&root, str2);

            if (fireman->firstchild == NULL)
            {
                if (fireman == fireman->father->firstchild)
                {
                    fireman->father->firstchild = fireman->rightbrother;
                    free(fireman);
                }
                else
                {
                    for (TPtr p = fireman->father->firstchild; p->rightbrother != NULL; p = p->rightbrother)
                    {
                        if (p->rightbrother == fireman)
                        {
                            p->rightbrother = fireman->rightbrother;
                            free(fireman);
                            break;
                        }
                        
                    }
                }
            }
            
            else
            {
                UPTNode(fireman->firstchild);
            }
            
            
        }
        else if (!strcmp(str1, "print"))    //ppppppppppppprint
        {
            getchar();
            PrintTree(&root);
            printf("------------------------------------------------------------\n");
        }
        else
        {
            scanf("%s%s", str2, str3);
            getchar();
            TPtr older = FindPerson(&root, str1);

            TPtr newman;
            newman = (TPtr)malloc(sizeof(TNode));
            INITTNode(newman);
            newman->degree = older->degree +1;
            newman->father = older;
            strcpy(newman->name, str3);
            
            if (older->firstchild == NULL)
            {
                older->firstchild = newman;
            }
            else
            {
                for (TPtr p = older->firstchild; p != NULL; p = p->rightbrother)
                {
                    if (p->rightbrother == NULL)
                    {
                        p->rightbrother = newman;
                        break;
                    }
                }
            }
        }      
    }
    

    return 0;
}

void INITTNode(TPtr T)
{
    T->name[0] = '#';
    T->firstchild = NULL;
    T->rightbrother = NULL;
    T->father = NULL;
    T->degree = 0;
    return;
}
TPtr FindPerson(TPtr T, char* name)
{
    TPtr ans;
    if (T == NULL)
    {
        return NULL;
    }
    else if (!strcmp(T->name, name))
    {
        return T;
    }
    else
    {
        for (TPtr p = T->firstchild; p != NULL; p = p->rightbrother)
        {
            ans = FindPerson(p, name);
            if(ans != NULL)
                return ans;
        }
        return NULL;
    }
}
void Printplus(TPtr T)
{
    for (int i = T->degree; i > 0; i--)
    {
        printf("+");
    }
}
void PrintTree(TPtr T)
{
    if (T != NULL)
    {
        Printplus(T);
        puts(T->name);
        for (TPtr p = T->firstchild; p != NULL; p = p->rightbrother)
        {
            PrintTree(p);
        }
    }
}
void UPTNode(TPtr T)
{
    if (T->firstchild == NULL)
    {
        strcpy(T->father->name, T->name);
        T->father->firstchild = T->rightbrother;
        free(T);
    }
    else
    {
        strcpy(T->father->name, T->name);
        UPTNode(T->firstchild);
    } 
}