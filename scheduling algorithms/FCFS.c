#include <stdio.h>

#define MAX 100

struct Process
{
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completion;
};

// Function to sort processes by arrival time (using Bubble Sort)
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

// Function to implement First Come First Serve (FCFS) Scheduling
void fcfs(struct Process p[], int n)
{
    sort(p, n); // Sort processes by arrival time
    int time = 0; // Track current time

    for (int i = 0; i < n; i++)
    {
        // If CPU is idle, move time forward
        if (time < p[i].arrival)
        {
            time = p[i].arrival;
        }

        // Calculate process completion time
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion; // Update current time
    }

    // Display results
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
               p[i].pid, p[i].arrival, p[i].burst, 
               p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main()
{
    int n;

    // Get number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Check if n exceeds MAX
    if (n > MAX)
    {
        printf("Error: Maximum number of processes is %d\n", MAX);
        return 1;
    }

    struct Process p[MAX];

    // Get process details
    printf("Enter Process ID, Arrival Time, and Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
    }

    // Run FCFS Scheduling
    fcfs(p, n);   

    return 0;
}
