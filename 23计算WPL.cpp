#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef struct tnode{
	int type;
	int data;
	struct tnode *lchild, *rchild;
} TNode, *TPtr;

struct cmp {
	bool operator() (TNode a, TNode b)
	{
		return a.data > b.data;
	}
};

priority_queue< TNode, vector<TNode>, cmp > PQ;

int CreateHT(int n);
void INITTNode(TNode* T);

int main()
{
	int n;
	scanf("%d", &n); 
	for(int i = 0; i < n; i++)
	{
		TNode temp;
		INITTNode(&temp);
		scanf("%d", &temp.data);
		PQ.push(temp);
	}
	
	printf("WPL=%d\n", CreateHT(n));
	return 0;
}

int CreateHT(int n)
{
	int ans = 0;
	
	
	for(int i = 1; i < n; i++)
	{
		TNode n1 = PQ.top();
		PQ.pop();
	
		TNode n2 = PQ.top();
		PQ.pop();
		
		TPtr fa = (TPtr)malloc(sizeof(TNode));
		INITTNode(fa);
		fa->type = 1;
		fa->data = n1.data + n2.data; ans+= fa->data;
		fa->lchild = &n1;
		fa->rchild = &n2;
		
		PQ.push(*fa);
	}
	
	return ans;
}
void INITTNode(TNode* T)
{
	T->type = 0;
	T->data = 0;
	T->lchild = T->rchild = NULL; 
}
