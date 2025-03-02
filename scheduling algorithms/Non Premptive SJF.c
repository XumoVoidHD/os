#include <stdio.h>
#define MAX 100

struct Process {
    int pid, arrival, burst, waiting, turnaround, completion, executed;
};

void sjf(struct Process p[], int n) {
    int completed = 0, time = 0, minIndex;
    
    while (completed < n) {
        minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].executed) {
                if (minIndex == -1 || p[i].burst < p[minIndex].burst) {
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        time += p[minIndex].burst;
        p[minIndex].completion = time;
        p[minIndex].turnaround = p[minIndex].completion - p[minIndex].arrival;
        p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
        p[minIndex].executed = 1;
        completed++;
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

    printf("Enter Process ID, Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].executed = 0;
    }

    sjf(p, n);
    return 0;
}
