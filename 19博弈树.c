#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MaxSLength 100

typedef struct tnode {
	char data;										//节点数据类型 
	struct tnode *firstchild, *rightbrother;		//兄弟链表 
} TNode, *TPtr;


char* CreateTree( TPtr T, char *S );		// 根据字符串 S 建树 
void INITTNode(TPtr T);

int main()
{
	TNode root;
	INITTNode(&root);
	char S[MaxSLength];
	gets(S);
	CreateTree(&root, S);
	for(int i = 0; S[i] != '\0'; i++)
		if(S[i] != '(' && S[i] != ')' && S[i] != ',')
			printf("%c\n", S[i]);
	char cont = 'y';
	while(cont != 'n')
	{
		int player;
		TPtr current = &root;
		printf("Who play first(0: computer; 1: player )?\n");
		scanf("%d", &player);
		getchar(); 
		int endflag = 0;		//1:computer 2:human
		while(!endflag)
		{
			if(player == 0)
			{
				TPtr child;
				
				for(child = current->firstchild; child->rightbrother != NULL; child = child->rightbrother)
				{
					if(child->firstchild == NULL)
					{
						endflag = 1;
						break;
					}
				}
				if(child->firstchild == NULL)
					endflag = 1;
				current = child;
				printf("computer: %c\n", current->data);
				player = 1;
			}
			else
			{
				char inputc;
				TPtr child;
				//check
				int checkflag = 0;
				while(!checkflag)
				{
					printf("player:\n");
					scanf("%c", &inputc);
					getchar();
					for(child = current->firstchild; child->rightbrother != NULL; child = child->rightbrother)
					{
						if(child->data == inputc)
						{
							checkflag = 1;
							break;
						}
					}
					if(child->data == inputc)
						checkflag = 1;
					if(!checkflag)
						printf("illegal move.\n");
					else
						current = child;
				}
				if(current->firstchild == NULL)
					endflag = 2;
				player = 0;
			}
		}
		if(endflag == 1)
			printf("Sorry, you lost.\n");
		else
			printf("Congratulate, you win.\n");
		printf("Continue(y/n)?\n");
		scanf("%c", &cont);
		getchar();
	}
	
	return 0;
}

char* CreateTree( TPtr T, char *S )
{
	char* temps = ++S;
	TPtr temp1 = T;
	T->data = *temps++;
	while(*temps != ')')
	{
		if(*temps == ',')
			temps++;
		else if(*temps == '(')	//数据输入 
		{
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
	return ++temps;
}

void INITTNode(TPtr T)
{
	T->data = '#';
	T->firstchild = NULL;
	T->rightbrother = NULL;
}
