#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int main()
{
    int D[10];
    priority_queue<int,vector<int> >T;//这里注意要多打一个空格
    for(int i=0;i<10;i++)
    {
        D[i]=(i*10/3+372)%20;//随意获取10个数
        printf("%d ",D[i]);
        T.push(D[i]);
    }
    printf("\n----------分割线-----------\n");
    while(!T.empty())
    {
        int s=T.top();
        printf("%d ",s);
        T.pop();//出队
    }
    return 0;
}
