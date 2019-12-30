#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define MAXNUM 100
#define Cutoff 5

int Qinput(int *qlist);
int ctoi(char *c);
void Myswap(int *a, int *b);
void Myqsort(int *qlist, int left, int right);
void Insertsort(int *qlist, int left, int right);
int Median3(int *qlist, int left, int right);

queue<int> q;

int main()
{
    int qlist[MAXNUM];
    int num = Qinput(qlist);
    Myqsort(qlist, 0, num - 1);

    printf("After Sorting:\n");
    for (int i = 0; i < num; i++)
    {
        printf("%d ", qlist[i]);
    }
    printf("\nMedian3 Value:\n");

    if (q.empty())
    {
        printf("none\n");
    }
    else
    {
        while (!q.empty())
        {
            printf("%d ", q.front());
            q.pop();
        }
        printf("\n");
    }

    return 0;
}

int Qinput(int *qlist)
{
    char temp[10];
    int num = 0;
    scanf("%s", temp);
    getchar();
    while (temp[0] != '#')
    {
        qlist[num++] = ctoi(temp);
        scanf("%s", temp);
        getchar();
    }
    return num;
}

int ctoi(char *c)
{
    int x = 1;
    int ans = 0;

    for (int i = strlen(c) - 1; i >= 1; i--)
    {
        ans += (c[i] - '0') * x;
        x *= 10;
    }

    if (c[0] == '-')
    {
        ans *= -1;
    }
    else
    {
        ans += (c[0] - '0') * x;
    }

    return ans;
}

void Myswap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Insertsort(int *qlist, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int a = i;
        while (a - 1 >= left && qlist[a] < qlist[a - 1])
        {
            Myswap(&(qlist[a]), &(qlist[a - 1]));
            a--;
        }
    }
}

int Median3(int *qlist, int left, int right)
{
    int center = (left + right) / 2;
    int a = qlist[left], b = qlist[center], c = qlist[right];
    if ((a > b && a < c) || (a > c && a < b))
    {
        ;
    }
    else if ((b > a && b < c) || (b > c && b < a))
    {
        Myswap(&qlist[center], &qlist[left]);
    }
    else
    {
        Myswap(&qlist[right], &qlist[left]);
    }

    return qlist[left];
}

void Myqsort(int *qlist, int left, int right)
{
    if (left + Cutoff > right)
    {
        Insertsort(qlist, left, right);
    }
    else
    {
        int i, j, pivot;
        pivot = Median3(qlist, left, right);
        q.push(pivot);
        i = left + 1;
        j = right;

        while (1)
        {
            while (qlist[i++] <= pivot)
                ;
            i--;
            while (qlist[j--] >= pivot)
                ;
            j++;
            if (i < j)
            {
                Myswap(&qlist[i++], &qlist[j--]);
            }
            else
            {
                break;
            }
        }

        Myswap(&qlist[left], &qlist[j]);
        Myqsort(qlist, left, j - 1);
        Myqsort(qlist, j + 1, right);
    }
}