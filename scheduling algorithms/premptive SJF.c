#include <stdio.h>
#include <limits.h>
#define MAX 100

struct Process {
    int pid, arrival, burst, remaining, waiting, turnaround, completion;
};

void srtf(struct Process p[], int n) {
    int completed = 0, time = 0, minIndex;
    int shortestRemaining = INT_MAX;

    while (completed < n) {
        minIndex = -1;
        shortestRemaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < shortestRemaining) {
                shortestRemaining = p[i].remaining;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        p[minIndex].remaining--;

        if (p[minIndex].remaining == 0) {
            completed++;
            p[minIndex].completion = time + 1;
            p[minIndex].turnaround = p[minIndex].completion - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
        }
        time++;
    }

    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[MAX];

    printf("Enter Process ID, Arrival Time, and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    srtf(p, n);
    return 0;
}
