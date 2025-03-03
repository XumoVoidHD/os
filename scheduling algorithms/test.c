#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

// Structure to represent a process
typedef struct Process
{
    int id;              // Process ID
    int arrival_time;    // Arrival time
    int burst_time;      // Burst time (execution time required)
    int remaining_time;  // Remaining burst time
    int completion_time; // Time at which process completes
    int waiting_time;    // Total waiting time
    int turnaround_time; // Time from arrival to completion
} Process;

void roundRobinScheduling(Process p[], int n, int time_quantum)
{
    int *queue = (int *)malloc(sizeof(int) * 100);
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++)
    {
        p[i].remaining_time = p[i].burst_time;
    }

    int time = 0;
    int completed = 0;

    for (int i = 0; i < n; i++)
    {
        if (p[i].arrival_time == 0)
        {
            queue[rear] = i;
            rear++;
        }
    }

    while (completed != n)
    {
        if (rear == front)
        {
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (p[i].remaining_time > 0 && p[i].arrival_time > time)
                {
                    if (p[i].arrival_time < next_arrival)
                    {
                        next_arrival = p[i].arrival_time;
                    }
                }
            }

            time = next_arrival;

            for (int i = 0; i < n; i++)
            {
                if (p[i].arrival_time == next_arrival && p[i].remaining_time > 0)
                {
                    queue[rear] = i;
                    rear++;
                }
            }
            continue;
        }

        int idx = queue[front];
        front++;

        if (p[idx].remaining_time == 0)
        {
            continue;
        }

        int execution_time = (p[idx].remaining_time < time_quantum) ? p[idx].remaining_time : time_quantum;

        p[idx].remaining_time -= execution_time;
        time += execution_time;

        for (int i = 0; i < n; i++)
        {
            if(p[i].remaining_time > 0 && p[i].arrival_time > time - execution_time && p[i].arrival_time <= time)
            {
                queue[rear] = i;
                rear++;
            }
        }

        if(p[idx].remaining_time > 0)
        {
            queue[rear] = idx;
            rear++;
        }
        else
        {
            completed++;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        }
    }
    free(queue);
}