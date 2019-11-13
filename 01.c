#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
	int number;
	struct person * next;
};

int main(void)
{
	int n, k, m;
	scanf("%d,%d,%d", &n, &k, &m);
	if(n < 1 || k < 1 || m < 1)
		printf("n,m,k must bigger than 0.\n");
	else if(k > n)
		printf("k should not bigger than n.\n");
	else
	{
		struct person * head = NULL;
		struct person * prev, * current;
		struct person * start = NULL;
		for(int i = 1; i <= n; i++)
		{
			current = (struct person *) malloc(sizeof(struct person));
			if(head == NULL)
				head = current;
			else
				prev->next = current;
			current->next = NULL;
			current->number = i;
			if(i == k+1)
				start = prev;
			prev = current;
		}
		current->next = head;
		
		int j = 1;
		while((start->next) != start)
		{
			current = start;
			for(int i = 1; i < m; i++)
			{
				current = current->next;
			}
			if(j != 10)
			{
				printf("%d ", current->number);
				j++;
			}
			else
			{
				printf("%d\n", current->number);
				j = 1;
			}
			start = current->next;
			prev = current;
			while(prev->next != current)
				prev = prev->next;
			prev->next = start;
			free(current);
		}
		printf("%d\n", start->number);
	}	
	return 0;
}
