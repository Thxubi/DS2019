#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100
#define MAXI 10000

typedef struct {
	int i, j;		//行·列
	int value;
} Tnode;

typedef struct {
	Tnode data[MAXSIZE+1];
	int rpos[MAXI+1];
	int mu, nu, tu;
} TMartix;

TMartix A, B, Q;

void Input();

int main()
{
	Input();
	
	Q.mu = A.mu; Q.nu = B.nu; Q.tu = 0;
	
	int ccol;
	for(int i = 1; i <= A.mu; i++)		//A的每一行 
	{
		int ctemp[MAXI] = {0};
		
		Q.rpos[i] = Q.tu + 1;
		
		int maxj;
		if(i < A.mu)
			maxj = A.rpos[i+1];
		else
			maxj = A.tu + 1;
		
		for(int j = A.rpos[i]; j < maxj; j++)
		{
			int bi = A.data[j].j;
			
			int maxk;
			if(bi < B.mu)
				maxk = B.rpos[bi+1];
			else
				maxk = B.tu + 1;
			 
			for(int k = B.rpos[bi]; k < maxk; k++)
			{
				ccol = B.data[k].j;
				ctemp[ccol] += A.data[j].value * B.data[k].value;
			}
		}	
		for(ccol = 1; ccol <= Q.nu; ccol++)
			if(ctemp[ccol])
			{
				Q.tu++;
				Q.data[Q.tu].i = i;
				Q.data[Q.tu].j = ccol;
				Q.data[Q.tu].value = ctemp[ccol];
			}	
		
	}
	printf("%d\n%d\n%d\n", Q.mu, Q.nu, Q.tu);
	for(int i = 1; i <= Q.tu; i++)
		printf("%d,%d,%d\n", Q.data[i].i, Q.data[i].j, Q.data[i].value);
	
	return 0;
}

void Input()
{
	int num, temp;
	scanf("%d%d%d", &A.mu, &A.nu, &A.tu);
	memset(A.rpos, 0, (A.mu+1)*sizeof(int));
	for(int i = 1; i <= A.tu; i++)
	{
		scanf("%d%d%d", &A.data[i].i, &A.data[i].j, &A.data[i].value);
		A.rpos[A.data[i].i] ++;
	}
	num = A.rpos[1];
	A.rpos[1] = 1;
	for(int i = 2; i <= A.mu; i++)
	{
		temp = A.rpos[i];
		A.rpos[i] = A.rpos[i-1] + num;
		num = temp;
	}
	scanf("%d%d%d", &B.mu, &B.nu, &B.tu);
	memset(B.rpos, 0, (B.mu+1)*sizeof(int));
	for(int i = 1; i <= B.tu; i++)
	{
		scanf("%d%d%d", &B.data[i].i, &B.data[i].j, &B.data[i].value);
		B.rpos[B.data[i].i] ++;
	}
	num = B.rpos[1];
	B.rpos[1] = 1;
	for(int i = 2; i <= B.mu; i++)
	{
		temp = B.rpos[i];
		B.rpos[i] = B.rpos[i-1] + num;
		num = temp;
	}
}
