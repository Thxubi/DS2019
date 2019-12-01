#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MaxSLength 100

typedef struct tnode {
	char data;										//节点数据类型 
	struct tnode *firstchild, *rightbrother;		//兄弟链表 
	int degree;
} TNode, *TPtr;


char* CreateTree(TPtr T, char *S);		// 根据字符串 S 建树 
void INITTNode(TPtr T);
void PrintTree(TPtr T, int n);
void printtab(int n);

int degree[MaxSLength] = {0};
int maxdegree = 0;

int main()
{
	TNode root;
	INITTNode(&root);
	char S[MaxSLength];
	gets(S);
	CreateTree(&root, S);
	PrintTree(&root, 0);
	
	printf("Degree of tree: %d\n", maxdegree);
	for(int i = 0; i <= maxdegree; i++)
		printf("Number of nodes of degree %d: %d\n", i, degree[i]);
	
	return 0;
}

void PrintTree(TPtr T, int n)
{
	while(T != NULL)
	{
		if(T->data != '#')
		{
			printtab(n);
			printf("%c\n", T->data);
		//
		degree[T->degree]++;
		maxdegree = T->degree > maxdegree ? T->degree : maxdegree;
		//
		}
		if(T->firstchild != NULL)
		{
			PrintTree(T->firstchild, n+1);
		}
		T = T->rightbrother;
	}
}

void printtab(int n)
{
	for(int i = 0; i < n; i++)
		printf("    ");
}

char* CreateTree(TPtr T, char *S)
{
	char* temps = ++S;
	TPtr temp1 = T;
	if(*temps != ')')
		T->data = *temps++;
	int degree = 0;
	while(*temps != ')')
	{
		if(*temps == ',')
			temps++;
		else if(*temps == '(')
		{
			degree ++;
			if(T->firstchild == NULL)
			{
				temp1 = (TPtr)malloc(sizeof(TNode));
				T->firstchild = temp1;
			}
			else
			{
				temp1->rightbrother = (TPtr)malloc(sizeof(TNode));
				temp1 = temp1->rightbrother;
			}
			INITTNode(temp1); 
			temps = CreateTree(temp1, temps);
		}
	}
	T->degree = degree;
	return ++temps;
}

void INITTNode(TPtr T)
{
	T->data = '#';
	T->firstchild = NULL;
	T->rightbrother = NULL;
}
