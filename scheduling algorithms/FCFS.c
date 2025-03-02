#include <stdio.h>
#define MAX 100

struct Process
{
    float pid;
    float arrival;
    float burst;
    float waiting;
    float turnaround;
    float completion;
};

void sort(struct Process p[], int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (p[j].arrival > p[j + 1].arrival)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfs(struct Process p[], int n)
{
    sort(p, n);
    int time = 0;

    for (int i = 0; i < n; i++)
    {
        if (time < p[i].arrival)
        {
            time = p[i].arrival;
        }

        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion;
    }

    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[MAX];

    printf("Enter Process ID, Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
    }

    return 0;
}