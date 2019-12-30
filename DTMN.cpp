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

#define Up 1
#define Down -1
//下面是可变参数
#define Midfloor 10
#define Waittime 2

typedef struct person
{
    int start;
    int end;
    float waittime;
} Person, *PersonPtr;

typedef struct qnode
{
    PersonPtr data;
    struct qnode *next;
} QNode, *QPtr;

typedef struct
{
    QPtr front;
    QPtr rear;
} LinkQueue;

typedef struct dt
{
    int peoplenum;
    int pp[23];
    int Currentfloor;
    int Nextfloor;
    float isWaiting; // 判断停止/运行
    int Condintion;  // Up or Down
    int level;       //判断是哪类电梯
    int isFree;
} Dianti, *DiantiPtr;

void INITQue(LinkQueue *Q);
void INQue(LinkQueue *Q, PersonPtr person);
int OUTQue(LinkQueue *Q, PersonPtr *popdata);
int QueLength(LinkQueue *Q);

void INITDianti(DiantiPtr d);
void DiantiFree(DiantiPtr d);
void GetNextfloor(DiantiPtr d);
int Upfinder(DiantiPtr d);
int Downfinder(DiantiPtr d);
void Waittimeplus();

LinkQueue Floor[23];

int main()
{
    int flag = 1;

    while (flag)
    {
        int satisnum, unsatisnum, sumnum, diantinum, fucknum = 0;
        unsatisnum = satisnum = sumnum = diantinum = 0;
        printf("How many Dianti do you have?\n");
        scanf("%d", &diantinum);
        getchar();

        //创建diantinum个电梯
        Dianti *dt;
        dt = (Dianti *)calloc(diantinum, sizeof(Dianti));

        for (int i = 0; i < diantinum; i++)
        {
            INITDianti(&dt[i]);
            if (i < (diantinum / 2) - 1)
            {
                dt[i].level = Midfloor;
            }
        }

        for (int i = 0; i < 23; i++)
        {
            INITQue(&Floor[i]);
        }
        freopen("data.txt", "r", stdin);

        float time = 0;
        int inttime = 0;
        int end = 0;
        int inflag = 1;

        while (!end)
        {
            inttime = time;
            if (time == 840)
            {
                inflag = 0;
                scanf("%d", &sumnum);
            }

            if (inflag && (time - inttime) == 0) //生成people
            {
                int innum, outnum;
                scanf("%d%d", &innum, &outnum);
                for (int i = 0; i < innum; i++)
                {
                    PersonPtr p = (PersonPtr)malloc(sizeof(Person));
                    p->start = 1;
                    scanf("%d", &p->end);
                    p->waittime = 0;
                    if (p->end <= dt[0].level)
                    {
                        INQue(&Floor[0], p); // 0 代表低层
                    }
                    else
                    {
                        INQue(&Floor[1], p); // 1 代表高层
                    }
                }
                for (int i = 0; i < outnum; i++)
                {
                    PersonPtr p = (PersonPtr)malloc(sizeof(Person));
                    p->end = 1;
                    scanf("%d", &p->start);
                    p->waittime = 0;
                    INQue(&Floor[p->start], p);
                }
            }

            for (int i = 0; i < diantinum; i++)
            {
                DiantiFree(&dt[i]);
                if (!dt[i].isFree)
                {
                    GetNextfloor(&dt[i]);
                    if (!dt[i].isWaiting)
                    {
                        dt[i].Currentfloor += dt[i].Condintion;
                        if (dt[i].Nextfloor == dt[i].Currentfloor) //  电梯在下一次要停了
                        {
                            dt[i].isWaiting = -1 * Waittime;
                        }
                    }

                    else
                    {
                        if (dt[i].isWaiting == -1 * Waittime)
                        {
                            dt[i].peoplenum -= dt[i].pp[dt[i].Currentfloor]; // 下人
                            dt[i].pp[dt[i].Currentfloor] = 0;
                        }
                        dt[i].isWaiting += 0.5;

                        while (dt[i].peoplenum != 10 && Floor[dt[i].Currentfloor].front != Floor[dt[i].Currentfloor].rear)
                        { //电梯上人
                            PersonPtr p;

                            if (dt[i].Currentfloor == 1 && dt[i].level == Midfloor)
                            {
                                if (Floor[0].front != Floor[0].rear)
                                {
                                    OUTQue(&Floor[0], &p);
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                OUTQue(&Floor[dt[i].Currentfloor], &p);
                            }

                            if (p->waittime <= 6)
                            {
                                satisnum++;
                            }
                            else
                            {
                                unsatisnum++;
                            }

                            dt[i].peoplenum++;

                            dt[i].pp[p->end]++;

                            free(p);
                        }

                        if (dt[i].peoplenum == 10) //人满
                        {
                            dt[i].isWaiting = 0;
                        }

                        if (dt[i].level == 22 && dt[i].Currentfloor <= Midfloor)
                        {
                            dt[i].isWaiting = 0;
                        }
                    }
                }
            }

            Waittimeplus();

            if (time == 843)
            {
                end = 1;
            }
            //printf("%f\n", time);
            time += 0.5;
        }

        free(dt);
        fclose(stdin);
        freopen("CON", "r", stdin);
        freopen("CON", "w", stdout);
        float perc;
        perc = ((float)satisnum / sumnum) * 100;
        printf("Satisfied percentage: %f %\n", perc);
        printf("continue?(y/n)\n");
        if (getchar() == 'y')
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }
    }
    return 0;
}

void INITQue(LinkQueue *Q)
{
    Q->front = Q->rear = (QPtr)malloc(sizeof(QNode));
    Q->front->next = NULL;
}

void INQue(LinkQueue *Q, PersonPtr person)
{
    QPtr p;
    p = (QPtr)malloc(sizeof(QNode));
    p->data = person;
    p->next = NULL;

    Q->rear->next = p;
    Q->rear = p;
}

int OUTQue(LinkQueue *Q, PersonPtr *popdata)
{
    if (Q->front == Q->rear)
        return 0;
    QPtr p;
    PersonPtr e;
    p = Q->front->next;
    e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    *popdata = e;
    return 1;
}

int QueLength(LinkQueue *Q)
{
    int i = 0;
    QPtr p;
    p = Q->front;
    for (i = 0; p != Q->rear; i++)
    {
        p = p->next;
    }
    return i;
}

void INITDianti(DiantiPtr d)
{
    d->peoplenum = 0;
    memset(d->pp, 0, sizeof(d->pp[0]));
    d->Currentfloor = 1;
    d->Nextfloor = 0;
    d->isFree = 1;
    d->isWaiting = -1 * Waittime;
    d->Condintion = Up;
    d->level = 22;
}

void DiantiFree(DiantiPtr d)
{
    if (d->Currentfloor == 1)
    {
        if (d->level == Midfloor && Floor[0].front != Floor[0].rear)
        {
            d->isFree = 0;
            return;
        }
        if (d->level == 22 && Floor[1].front != Floor[1].rear)
        {
            d->isFree = 0;
            return;
        }
    }
    else
    {
        if (Floor[d->Currentfloor].front != Floor[d->Currentfloor].rear)
        {
            d->isFree = 0;
            return;
        }
    }

    if (d->peoplenum != 0)
    {
        d->isFree = 0;
        return;
    }
    else
    {
        if (Upfinder(d) == 0 && Downfinder(d) == 0)
        {
            d->isFree = 1;
        }
        else
        {
            d->isFree = 0;
        }
        return;
    }
}

void GetNextfloor(DiantiPtr d)
{
    if (d->isWaiting != 0)
    {
        return;
    }

    if (d->Condintion == Up)
    {
        int nextfloor;

        nextfloor = Upfinder(d);
        if (nextfloor != 0)
        {
            d->Nextfloor = nextfloor;
            return;
        }

        d->Condintion = Down;
        nextfloor = Downfinder(d);
        if (nextfloor != 0)
        {
            d->Nextfloor = nextfloor;
            return;
        }

        d->Nextfloor = d->Currentfloor;
        return;
    }

    else
    {
        int nextfloor;

        nextfloor = Downfinder(d);
        if (nextfloor != 0)
        {
            d->Nextfloor = nextfloor;
            return;
        }

        d->Condintion = Up;
        nextfloor = Upfinder(d);
        if (nextfloor != 0)
        {
            d->Nextfloor = nextfloor;
            return;
        }

        d->Nextfloor = d->Currentfloor;
        return;
    }
}

int Upfinder(DiantiPtr d)
{
    int nextfloor;
    for (nextfloor = d->Currentfloor + 1; nextfloor < d->level + 1; nextfloor++)
    {
        if (d->pp[nextfloor] != 0)
        {
            break; //有人要下
        }

        else if (d->peoplenum != 10 && Floor[nextfloor].front != Floor[nextfloor].rear)
        {
            break; //有人要上
        }
    }

    if (nextfloor != d->level + 1)
    {
        return nextfloor;
    }

    else
    {
        return 0;
    }
}
int Downfinder(DiantiPtr d)
{
    int nextfloor;
    for (nextfloor = d->Currentfloor - 1; nextfloor > 0; nextfloor++)
    {
        if (d->pp[nextfloor] != 0)
        {
            break; //有人要下
        }

        else if (d->peoplenum != 10 && nextfloor != 1 && Floor[nextfloor].front != Floor[nextfloor].rear)
        {
            break; //有人要上
        }
        else if (nextfloor == 1)
        {
            if (d->level == 22 && Floor[1].front != Floor[1].rear)
            {
                break;
            }
            if (d->level == Midfloor && Floor[0].front != Floor[0].rear)
            {
                break;
            }
        }
    }

    if (nextfloor != 0)
    {
        return nextfloor;
    }

    else
    {
        return 0;
    }
}

void Waittimeplus()
{
    for (int i = 1; i <= 22; i++)
    {
        for (QPtr p = Floor[i].front->next; p != NULL; p = p->next)
        {
            p->data->waittime += 0.5;
        }
    }
}