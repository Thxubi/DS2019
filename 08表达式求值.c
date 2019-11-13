#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
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
void INIT();
int ctype(int c, int bfc);				//op:0 number:1 -number:-1	end:-2
void tempnum_input();
int compare(int a, int b);
int operate();

LinkStack op, num, tempnum;
char oplist[] = {'+', '-', '*', '/', '%', '^', '(', ')', 10};
int complist[6][6] = {				//	>:1		<:0		=:-1	error:-2
	{1, 0, 0, 0, 1, 1},
	{1, 1, 0, 0, 1, 1},
	{1, 1, 0, 0, 1, 1},
	{0, 0, 0, 0, -1, -2},
	{1, 1, 1, -2, 1, 1},
	{0, 0, 0, 0, -2, -1}
};

int main()
{
	int total, temp;
	scanf("%d", &total);
	getchar();
	while(total--)
	{
		INIT();
		INStack(&op, 10);
		int c, bfc = 10;
		c = getchar();
//		printf("\t\t%d\n", c);
		while(c != 10 || op.top->data != 10)
		{
//			printf("\t%d %d\n", bfc, c);
			//数字进数字栈
			if(ctype(c, bfc) == -1)
			{
				tempnum.base->data = -1;
				bfc = c;
				c = getchar();
//				printf("\t\t%c in op\n", c);
			}
			else if(ctype(c, bfc) == 1)
			{
				INStack(&tempnum, c - '0');
				bfc = c;
				c = getchar();
//				printf("\t\t%c in op\n", c);
			}
			//运算符进op栈 
			else if(ctype(c, bfc) == -2)
				goto ERR;
			else
			{
				if(tempnum.top != tempnum.base)
					tempnum_input();						//number in
				switch(compare(op.top->data, c))
				{	
					case 0:		//<
						INStack(&op, c);
						bfc = c;
						c = getchar();
						break;
					case -1:	//=
						OUTStack(&op, &temp);
						bfc = c;
						c = getchar();
						break;
					case 1:
						switch(operate())
						{
							case 0:
								goto ERR;
								break;
							case -1:
								goto END;
								break;
							default:;
						}
						break;
					case -2:
						goto ERR;
						break;
				}
			}
		}
//		printf("%d %d\n", StackSize(&num), StackSize(&op));
		if(num.top->next != num.base || op.top->next != op.base)
			goto ERR;
		printf("%d\n", num.top->data);
		if(0)		
		{
ERR:		printf("error.\n");
END:		while(c != 10)
				c = getchar();
		}
	}
}

int operate()
{
	int a, theta, b, c = 1, flag = 1;
//	printf("***\n");
	if(OUTStack(&op, &theta) == 0)
		flag = 0;
	else if(OUTStack(&num, &b) == 0)
		flag = 0;
	else if(OUTStack(&num, &a) == 0)
		flag = 0;
	
	if(flag != 0)
	{
//		printf("\t\t%d %c %d\n", a, theta, b);
		switch(theta)
		{
			case '+':
				c = a + b; break;
			case '-':
				c = a - b; break;
			case '*':
				c = a * b; break;
			case '/':
				if(b == 0)
				{
					printf("Divide 0.\n");
					flag = -1;
					break;
				}
				c = a / b; break;
			case '^':
				if(b < 0)
				{
					flag = 0;
					break;
				}
				if(b == 0)
				{
					c = 1;
					break;
				}
				while(b--)
					c *= a;
				break;
			case '%':
				c = a % b; break;
			default :
				flag = 0;
		}
	}
	if(flag == 1)
		INStack(&num, c);
//	printf("\t\t\t%d in num\n", c);
	return flag; 
}

int compare(int a, int b)
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
			case '%': case '^' :
				c[i] = 2;
				break;
			case '(':
				c[i] = 3;
				break;
			case ')':
				c[i] = 4;
				break;
			case 10:
				c[i] = 5;
				break;
		}
	
	return complist[c[0]][c[1]];
}

int ctype(int c, int bfc)		//op:0	num:1	-num:-1		error:-2
{
	if(c == 10) 
		return -3;							//end
	if(c == '-')
	{
		for(int i = 0; oplist[i] != '\0'; i++)
			if(bfc == oplist[i] && bfc != ')')
				return -1;					//-num
		return 0;
	}
	if(c == '(' && (bfc <= 57 && bfc >= 48))//这题我服了 
		return -2;
	for(int i = 0; oplist[i] != 10; i++)
		if(c == oplist[i])
			return 0;						//op
	return 1;								//num
}

void tempnum_input()
{
	int m, n = 0;
	for(int i = 1; tempnum.base != tempnum.top; i*=10)
	{
		OUTStack(&tempnum, &m);
		n += m * i;
	}
	n *= tempnum.base->data;
	INStack(&num, n);
//	printf("\t\t\t%d in num\n", n);
	INITStack(&tempnum);
	tempnum.base->data = 1;
}

void INIT()
{
	INITStack(&op);
	INITStack(&num);
	INITStack(&tempnum);
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
	//检查操作 
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
