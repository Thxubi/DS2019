#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// ！！！这个程序非常不好，建议修改所有函数！！！ 
#define MaxSLength 100

typedef struct node {
	int Tag;		//1:list	0:atom
	char data;
	struct node *hp;
	struct node *tp;
} GList, *GPtr;


char* CreateGList( GPtr L, char *S );		// 根据字符串 S 表示的广义表内容建立广义表数据结构；
GList GetHead( GPtr L);					// 取表头运算
GList GetTail( GPtr L);					// 取表尾运算
void DestroyGList( GPtr L);					// 销毁广义表 L
void PrintGList( GPtr L);					// 显示广义表 L 内容
void INITGList(GPtr L);

int main()
{
	int i;
	GList L;
	INITGList(&L);
	char S[MaxSLength];
	gets(S);
	CreateGList(&L, S);
	
	printf("generic list: ");
	PrintGList(&L);
	printf("\n");
	while(&L != NULL)
	{
		scanf("%d", &i);
		if(i == 1)
		{
			if(L.hp == NULL)
			{
				printf("destroy tail\nfree list node\ngeneric list: ()\n");
				break; 
			}
			else if(L.hp->Tag == 0)
			{
				printf("destroy tail\nfree list node\ngeneric list: %c\n", L.hp->data);
				break;
			}
			else
				L = GetHead(&L);
			printf("\n");
		}
		else
		{
			if(L.tp == NULL)
			{
				printf("free head node\nfree list node\ngeneric list: ()\n");
				break;
			}
			L = GetTail(&L);
			printf("\n");
		}
	}
	return 0;
}

void INITGList(GPtr L)
{
	L->Tag = 1;
	L->hp = NULL;
	L->tp = NULL;
}
char* CreateGList( GPtr L, char *S )
{
	char* temps;
	GPtr temp1 = L, temp2;
	for(temps = S+1; *temps != ')'; temps++)
	{
		if(*temps == '(' && *(temps+1) == ')')
		{
			temp1->hp = NULL;
			temps++;
			if(*(temps+1) == ')')
				continue;
			temp1->tp = (GPtr)malloc(sizeof(GList));
			temp1 = temp1->tp;
			INITGList(temp1);
		}
		else if(*temps == '(')
		{
			
			temp2 = (GPtr)malloc(sizeof(GList));
			INITGList(temp2);
			temp1->hp = temp2;
			temps = CreateGList(temp2, temps);
			if(*(temps+1) == ')')
				continue;
			temp1->tp = (GPtr)malloc(sizeof(GList));
			temp1 = temp1->tp;
			INITGList(temp1);
		}
		else if(*temps == ',')
			continue;
		else
		{
			temp1->hp = (GPtr)malloc(sizeof(GList));
			temp1->hp->Tag = 0;
			temp1->hp->data = *temps;
			if(*(temps+1) == ')')
				continue;
			temp1->tp = (GPtr)malloc(sizeof(GList));
			temp1 = temp1->tp;
			INITGList(temp1);
		}
	}
	return temps;
}
GList GetHead( GPtr L)
{
	printf("destroy tail\nfree list node\ngeneric list: ");
	L = L->hp;	
	if(L->Tag == 1)
		PrintGList(L);
	else if(L->Tag == 0)
	{
		printf("(%c)", L->data);
		L = NULL;
	}
	return *L;
}
GList GetTail( GPtr L)
{
	printf("free head node\nfree list node\ngeneric list: ");
	L = L->tp;
	PrintGList(L);
	return *L;
}
void DestroyGList( GPtr L)
{
	GPtr temp1 = L, temp2;
	for(temp1; temp1 != NULL; temp1 = temp2)
	{
		if(temp1->hp->Tag == 0)
		{
			temp2 = temp1->tp;
			free(temp1->hp);
			free(temp1);
		}
		else
		{
			temp2 = temp1->tp;
			DestroyGList(temp1->hp);
			free(temp1);
		}
	}
}
void PrintGList( GPtr L)
{
	int flag = 0;
	GPtr temp1 = L, temp2;
	printf("(");
/*	if(L->Tag == 0)
		printf("%c\n", )*/
	for(temp1; temp1 != NULL; temp1 = temp1->tp)
	{
		if(flag)
			printf(",");
		if(temp1->hp == NULL)
		{
			printf("()");
			flag = 1;
		}
		else if(temp1->hp->Tag == 0)
		{
			printf("%c", temp1->hp->data);
			flag = 1;
		}
		else
		{
			temp2 = temp1->hp;
			PrintGList(temp2);
			flag = 1;
		}
	}
	printf(")");
}
