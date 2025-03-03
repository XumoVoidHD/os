#include <stdio.h>
#define MAX 100

struct Process {
    int pid, arrival, burst, priority, waiting, turnaround, completion, executed;
};

void priorityScheduling(struct Process p[], int n) {
    int completed = 0, time = 0, maxIndex;
    
    while (completed < n) {
        maxIndex = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].executed) {
                if (maxIndex == -1 || p[i].priority > p[maxIndex].priority) {
                    maxIndex = i;
                }
            }
        }

        if (maxIndex == -1) {
            time++;
            continue;
        }

        time += p[maxIndex].burst;
        p[maxIndex].completion = time;
        p[maxIndex].turnaround = p[maxIndex].completion - p[maxIndex].arrival;
        p[maxIndex].waiting = p[maxIndex].turnaround - p[maxIndex].burst;
        p[maxIndex].executed = 1;
        completed++;
    }

    printf("PID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].priority, p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[MAX];

    printf("Enter Process ID, Arrival Time, Burst Time, and Priority:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].executed = 0;
    }

    priorityScheduling(p, n);
    return 0;
}
