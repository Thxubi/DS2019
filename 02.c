#include <stdio.h>
#include <string.h>
#define MAX_A 100

struct student {
	int num;
	char name[16];
};

struct student list_1[MAX_A];
 
int main()
{
	int m, n;
	scanf("%d", &m);
	int i = m;
	while(i--)
	{
		scanf("%d", &list_1[m-i].num);
		getchar();
		scanf("%s", list_1[m-i].name);
	}
	
	scanf("%d", &n);
	if(n == 0)
		printf("the LIST2 is NULL.\n");
	else
	{
		int flag = 1;
		int nnumber;
		char nname[16];
		while(n--)
		{
			scanf("%d", &nnumber);
			getchar();
			scanf("%s", &nname);
			
			int j;
			for(j=1; j<=m; j++)
			{
				if(nnumber != list_1[j].num)
					continue;
				if(strcmp(nname, list_1[j].name) != 0)
					continue;
				else
					break;
			}
			if(j == m+1)
			{
				printf("%8d %s is not in LIST1.\n", nnumber, nname);
				flag = 0;
			}
		}
		
		if(flag)
			printf("the records of LIST2 are all in the LIST1.\n");
	}
}
