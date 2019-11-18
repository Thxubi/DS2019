#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef struct {
	int i, j;		//ÐÐ¡¤ÁÐ
	int value;
} Tnode;

typedef struct {
	Tnode data[MAXSIZE+1];
	int mu, nu, tu;
} TMartix;

TMartix M, T;
int num[101] = {0};
int cpot[101] = {0}; 

int main()
{
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	M.mu = a; M.nu = b; M.tu = c;
	for(int i = 1; i <= M.tu; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		M.data[i].i = x; M.data[i].j = y; M.data[i].value = z;
		num[y] ++;
	}
	cpot[1] = 1;
	for(int i = 2; i <= M.nu; i++)
		cpot[i] = cpot[i-1] + num[i-1];
	
	printf("num:");
	for(int i = 1; i <= M.nu; i++)
		printf("%d,", num[i]);
	printf("\ncpot:");
	for(int i = 1; i <= M.nu; i++)
		printf("%d,", cpot[i]);
	printf("\n");
		
	for(int i = 1; i <= M.tu; i++)
	{
		int tempj, q;
		tempj = M.data[i].j;
		q = cpot[tempj];
		T.data[q].i = M.data[i].j;
		T.data[q].j = M.data[i].i;
		T.data[q].value = M.data[i].value;
		cpot[tempj]++;
	}

	for(int i = 1; i <= M.tu; i++)
		printf("%d,%d,%d\n", T.data[i].i, T.data[i].j, T.data[i].value);
	return 0;
}
