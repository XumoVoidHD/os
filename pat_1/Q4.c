#include <stdio.h>

#define MAX 100

struct Process {
    int pid, arrival, burst, priority, waiting, turnaround, completion, executed;
};

struct Process p[MAX]; // Global array for processes
int n; // Number of processes

// Function to get input
void getInput() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Process ID, Arrival Time, Burst Time, and Priority:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].executed = 0; // Mark all as not executed
    }
}

// Function to sort processes by arrival time
void sortByArrival() {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to get the next process to be scheduled
int getNextProcess(int time) {
    int maxIndex = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= time && !p[i].executed) {
            if (maxIndex == -1 || p[i].priority < p[maxIndex].priority) { 
                maxIndex = i;
            }
        }
    }
    return maxIndex;
}

// Function to calculate completion, turnaround, and waiting times
void calculateTimes() {
    int completed = 0, time = 0;
    
    while (completed < n) {
        int idx = getNextProcess(time);
        
        if (idx == -1) {
            time++; // Idle CPU if no process is ready
            continue;
        }

        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        p[idx].executed = 1;
        completed++;
    }
}

// Function to display results
void displayResults() {
    float totalWT = 0, totalTAT = 0;
    
    printf("\nPID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", 
            p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
            p[i].completion, p[i].turnaround, p[i].waiting);
        
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

// Main function
int main() {
    getInput();
    sortByArrival();
    calculateTimes();
    displayResults();
    return 0;
}
