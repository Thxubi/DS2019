#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct snode {
	int width;
	int height;
	long long int time;
	struct snode * left;
	struct snode * right;
	struct snode * true_left;
	struct snode * true_right;
} SNode, * SPtr;

void INITStack();
void INStack(int w, int h);
SPtr talls(SPtr p);
SPtr shorts(SPtr p);
void Del_p(SPtr p);
void Get_Time();

SPtr current, lfwall, riwall, lf, ri;
long long int sumtime = 0;

int main()
{
	int n, i;
	scanf("%d", &n);
	i = n;
	INITStack();
	while(i--)
	{
		int w, h;
		scanf("%d%d", &w, &h);
		INStack(w, h);
	}
	i = n;
	while(i--)
	{
		Get_Time();
	}
	i = n;
	current = lfwall->right;
	while(i--)
	{
		printf("%lld\n", current->time);
		current = current->true_right;
	}
}

void INITStack()
{
	lfwall = (SPtr)malloc(sizeof(SNode));
	riwall = (SPtr)malloc(sizeof(SNode));
	lfwall->height = riwall->height = 1000001;
	lfwall->left = riwall->right = NULL;
	lf = lfwall;
	ri = riwall;
	current = lfwall;
}

void INStack(int w, int h)
{
	SPtr p;
	p = (SPtr)malloc(sizeof(SNode));
	p->left = p->true_left = lf;
	p->right = p->true_right = ri;
	p->height = h;
	p->width = w;
	lf->right = lf->true_right = p;
	ri->left = ri->true_left = p;
	
	if(h < current->height)
		current = p;
	lf = p;
}

SPtr talls(SPtr p)
{
	return (p->left->height) > (p->right->height) ? p->left : p->right;
}
SPtr shorts(SPtr p)
{
	return (p->left->height) < (p->right->height) ? p->left : p->right;
}

void Get_Time()
{
	SPtr p = current;
	if(p->height < shorts(p)->height)		// tall-short-tall
	{
		p->time = sumtime + p->width;
		sumtime += (shorts(p)->height - (p->height)) * p->width;
		Del_p(p);	
	}
	else		//s-m-l or l-m-s
	{
		while(shorts(p)->height < p->height)
		{
			p = shorts(p);
		}
		p->time = sumtime + p->width;
		sumtime += (shorts(p)->height - (p->height)) * p->width;
		Del_p(p);
	}
}

void Del_p(SPtr p)
{
	if(p->left->height < p->right->height)
	{
		p->left->right = p->right;
		p->left->width += p->width;
		current = p->left;
	}
	else
	{
		p->right->left = p->left;
		p->right->width += p->width; 
		current = p->right;
	}
}
