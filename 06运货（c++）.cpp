#include<queue>
#include<stack>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

void INIT();
void sim(int i);
int check();

stack <int> truck;
queue <int> bplat[110];

int n, s, q;
long long int sumtime;

int main()
{
	int set;
	scanf("%d", &set);
	while(set--)
	{
		scanf("%d%d%d", &n, &s, &q);
		INIT();
		for(int i = 1; i <= n; i++)
		{
			int temp, innum;
			scanf("%d", &innum);
			for(int j = 0; j < innum; j++)
			{
				scanf("%d", &temp);
				bplat[i].push(temp);
			}
			sim(i);
		}
		//others
		while(check() == 0)
		{
			for(int i = 1; i <= n; i++)
			{
				if(check() == 1) break;
				sim(i);
			}
		}
		printf("%lld\n", sumtime);
	}
}

void INIT()
{
	sumtime = -2;
}

int check()
{
	for(int i = 1; i <= n; i++)
	{
		if(bplat[i].empty())
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	if(truck.empty())
		return 1;
	else
		return 0;
}

void sim(int i)
{
	sumtime += 2;
	int temp;
	// out from truck
	while(!truck.empty())
	{
		if(truck.top() == i)
		{
			truck.pop();
			sumtime ++;
			continue;
		}
		else
		{
			if(bplat[i].size() == q)
				break;
			else
			{
				temp = truck.top();
				truck.pop();
				bplat[i].push(temp);
				sumtime++;
			}
		}
	}
	// load in truck
	while(truck.size() < s && !bplat[i].empty())
	{
		temp = bplat[i].front();
		bplat[i].pop();
		truck.push(temp);
		sumtime++;
	}
}
