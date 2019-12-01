#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSSIZE 100000

typedef struct bitnode {
	struct bitnode *lchild, *rchild;	// 0:left child		1:right child 
} BiTNode, *BiTPtr;

void INITBiTNode(BiTPtr T);

int main()
{
	int num, flag = 1, initflag = 0;
	scanf("%d", &num);
	getchar();			//		\n
	
	BiTNode root;
	INITBiTNode(&root);
	while(num-- && flag)
	{
		BiTPtr current = &root;
		char S[MAXSSIZE+1];
		gets(S);
		char temps = S[0];
		
		if((temps == '0' && current->lchild == NULL) || (temps == '1' && current->rchild == NULL))
			initflag = 1;
		else
			initflag = 0;
			
		int branchflag = 0;
		
		for(int i = 0; temps != '\0'; temps = S[++i])
		{
			if(temps == '0')
			{
				if(current->lchild == NULL && (branchflag || initflag))
				{
					current->lchild = (BiTPtr)malloc(sizeof(BiTNode));
					INITBiTNode(current->lchild);
				}
				else if(current->lchild == NULL && current->rchild != NULL)
				{
					branchflag = 1;
					current->lchild = (BiTPtr)malloc(sizeof(BiTNode));
					INITBiTNode(current->lchild);
				}
				else if(current->lchild == NULL)
				{
					flag = 0;
					break;
				}
				current = current->lchild;
			}
			else
			{
				if(current->rchild == NULL && (branchflag || initflag))
				{
					current->rchild = (BiTPtr)malloc(sizeof(BiTNode));
					INITBiTNode(current->rchild);
				}
				else if(current->rchild == NULL && current->lchild != NULL)
				{
					branchflag = 1;
					current->rchild = (BiTPtr)malloc(sizeof(BiTNode));
					INITBiTNode(current->rchild);
				}
				else if(current->rchild == NULL)
				{
					flag = 0;
					break;
				}
				current = current->rchild;
			}
		}
		if(flag == 0)
		{
			puts(S);
		}
		else if(current->lchild != NULL || current->rchild != NULL)
		{
			puts(S);
			flag = 0;
		}
	}
	if(flag)
		printf("YES\n");
	
	return 0;
}

void INITBiTNode(BiTPtr T)
{
	T->lchild = NULL;
	T->rchild = NULL;
}
