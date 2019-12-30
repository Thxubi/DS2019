#include <iostream>
#include <cstring>
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int rdfloor();              //产生随机楼层
int poisson();              //产生随机泊松数
int main()
{
    int num = 0;
    freopen("data.txt", "w", stdout);
    for (int i = 8; i < 22; i++)
    {
        int temp;
        for (int j = 0; j < 60; j++)
        {
            if (i == 8 || i == 13)
            {
                printf("20 2\n");
                num += 22;
                for (int k = 0; k < 20; k++)
                {
                    temp = rdfloor();
                    if (temp != 1)
                    {
                        printf("%d ", temp);
                    }
                    else
                    {
                        k--;
                    }
                }
                printf("\n");
                for (int k = 0; k < 2; k++)
                {
                    temp = rdfloor();
                    if (temp != 1)
                    {
                        printf("%d ", temp);
                    }
                    else
                    {
                        k--;
                    }
                }
                printf("\n");
            }
            else if (i == 11 || i == 18)
            {
                printf("2 20\n");
                num += 22;
                for (int k = 0; k < 2; k++)
                {
                    temp = rdfloor();
                    if (temp != 1)
                    {
                        printf("%d ", temp);
                    }
                    else
                    {
                        k--;
                    }
                }
                printf("\n");
                for (int k = 0; k < 20; k++)
                {
                    temp = rdfloor();
                    if (temp != 1)
                    {
                        printf("%d ", temp);
                    }
                    else
                    {
                        k--;
                    }
                }
                printf("\n");
            }
            else
            {
                int in = poisson();
                int out = poisson();
                num += in + out;
                printf("%d %d\n", in, out);
                for (int k = 0; k < in; k++)
                {
                    temp = rdfloor();
                    if (temp != 1)
                    {
                        printf("%d ", temp);
                    }
                    else
                    {
                        k--;
                    }
                }
                printf("\n");
                for (int k = 0; k < out; k++)
                {
                    temp = rdfloor();
                    if (temp != 1)
                    {
                        printf("%d ", temp);
                    }
                    else
                    {
                        k--;
                    }
                }
                printf("\n");
            }
        } 
    }
    printf("%d\n", num);
    fclose(stdout);
    return 0;
}

int rdfloor()
{
    static default_random_engine e(time(NULL));
    static uniform_int_distribution<int> u(1, 22);      //可变参数
    return u(e);
}
int poisson()
{
	static default_random_engine e(time(NULL));
    static poisson_distribution<int> d(5);              //可变参数
    return d(e);
}