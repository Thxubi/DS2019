#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

int getnum(int n, int m);

int main()
{
	int num;
	scanf("%d", &num);
	while(num--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		printf("%d\n", getnum(n, m));
	}
	
	return 0;
}

int getnum(int n, int m)
{
	if(m > 31)
		return getnum((n-(m-31)), 31);
	else if(n < m + 1)					//m层没有节点 
		return 0;
	else if(n == m + 1)				//单链树 
		return 1;
	else if(n >= pow(2, m+1) - 1)	//到m层刚好满树 
		return pow(2, m);
	else if(n > pow(2, m))
		return pow(2, m-1) + getnum(n-(pow(2, m)), m-1);
	else
		return getnum(n-1, m-1);
}
