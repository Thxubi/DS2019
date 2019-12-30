#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int paper[80000][2];

int main()
{
    int Num;
    scanf("%d", &Num);

    while (Num--)
    {
        int n;

        int ans = 0;
        scanf("%d", &n);
        int wall[80000] = {0};

        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &paper[i][0], &paper[i][1]);
        }

        for (int i = n - 1; i >= 0; i--)
        {
            int flag = 0;
            int left, right;
            left = paper[i][0];
            right = paper[i][1];

            for (int j = left; j <= right; j++)
            {
                if (wall[j] == 0)
                {
                    wall[j] = 1;
                    flag = 1;
                }
                else
                {
                    continue;
                }
            }

            if (flag)
            {
                ans++;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}