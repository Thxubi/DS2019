#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char data;
	struct node * next;
} Node, * Ptr;

typedef struct {
	Ptr top;
	Ptr base;
} LinkStack;

void INITStack(LinkStack *S);
void INStack(LinkStack *S, int data);
int OUTStack(LinkStack *S, int *popdata);
int StackSize(LinkStack *S);
void FREEStack(LinkStack *S);
int compare(char a, char b);

LinkStack op;
char oplist[] = {'+', '-', '*', '/', '^', '(', ')', '#'};
int complist[6][6] = {				//	>:1		<:0		=:-1	error:-2
	{0, 0, 0, 1, -2, 1},
	{1, 0, 0, 1, -2, 1},
	{1, 1, 1, 1, -2, 1},
	{1, 1, 1, 1, -2, 1},
	{0, 0, 0, -1, -2, -2},
	{0, 0, 0, -2, -2, -1}
};



int main ()
{
	int tt;
	scanf("%d", &tt);
	getchar();
	while(tt--)
	{
		INITStack(&op);
		INStack(&op, '#');
		char c = getchar();
		int temp;
		while(c != '#' || op.top->data != '#')
		{
			// numbers
			if((c >= 'a' && c <= 'z') || c >= 'A' && c <= 'Z')
			{
				printf("%c", c);
				c = getchar();
			}
			else
			{
				switch(compare(c, op.top->data))
				{
					case 1:					// in op stack
						INStack(&op, c);
						c = getchar();
						break;
					case 0:					//op.top out
						OUTStack(&op, &temp);
						printf("%c", temp);
						break;
					case -1:				// )
						OUTStack(&op, &temp);
						c = getchar();
						break;
					case -2:
						printf("E");
						break;
				}
			}
		}
		printf("\n");
		getchar();
	}
}

int compare(char a, char b)
{
	int c[2] = {a, b};
	for(int i = 0; i < 2; i++)
		switch(c[i])
		{
			case '+': case '-' :
				c[i] = 0;
				break;
			case '*': case '/' :
				c[i] = 1;
				break;
			case '^' :
				c[i] = 2;
				break;
			case '(':
				c[i] = 3;
				break;
			case ')':
				c[i] = 4;
				break;
			case '#':
				c[i] = 5;
				break;
		}
	
	return complist[c[0]][c[1]];
}

void INITStack(LinkStack *S)
{
	S->base = S->top = (Ptr)malloc(sizeof(Node));
	S->base->data = 1;
	S->base->next = NULL;
}

void INStack(LinkStack *S, int data)
{
	Ptr p;
	p = (Ptr)malloc(sizeof(Node));
	//¼ì²é²Ù×÷ 
	p->data = data;
	p->next = S->top;
	
	S->top = p;
}

int OUTStack(LinkStack *S, int *popdata)
{
	if(S->base == S->top) return 0;
	Ptr p;
	int e;
	p = S->top;
	e = p->data;
	S->top = p->next;
	free(p);
	*popdata = e;
	return 1;
}

int StackSize(LinkStack *S)
{
	Ptr temp = S->top;
	int i = 0;
	while(temp != S->base)
	{
		temp = temp->next;
		i++;
	}
	return i;
}

void FREEStack(LinkStack *S)
{
	Ptr temp;
	while(S->top != S->base)
	{
		temp = S->top;
		S->top = temp->next;
		free(temp);
	}
	free(S->base);
}
