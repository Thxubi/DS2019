#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define Maxnum 99999

int a[Maxnum] = {0};

void sort(int length, int t);
int main()
{
    int n;

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    int temp = 3;
    while (temp--)
    {
        for (int len = n / 2; len >= 1; len--)
            sort(len, n);
        for (int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        printf("\n");
        a[1] = a[n--];
    }

    return 0;
}

void sort(int length, int t)
{
    int i = 2 * length;
    
    int temp = a[length];
    while (1)
    {
        if (i > t)
            break;

        else if (i < t && a[i] < a[i + 1])
            i++;

        if (temp >= a[i])
            i = t + 1;

        else
        {
            a[length] = a[i];
            length = i;

            i *= 2;
        }
    }
    a[length] = temp;
}