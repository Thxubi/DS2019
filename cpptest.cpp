#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int main()
{
    int D[10];
    priority_queue<int,vector<int> >T;//����ע��Ҫ���һ���ո�
    for(int i=0;i<10;i++)
    {
        D[i]=(i*10/3+372)%20;//�����ȡ10����
        printf("%d ",D[i]);
        T.push(D[i]);
    }
    printf("\n----------�ָ���-----------\n");
    while(!T.empty())
    {
        int s=T.top();
        printf("%d ",s);
        T.pop();//����
    }
    return 0;
}
