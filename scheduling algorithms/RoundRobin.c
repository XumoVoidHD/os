#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a process
typedef struct Process {
    int id;             // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time (execution time required)
    int remaining_time; // Remaining burst time
    int completion_time;// Time at which process completes
    int waiting_time;   // Total waiting time
    int turnaround_time;// Time from arrival to completion
} Process;

// Function to implement Round Robin scheduling
void roundRobinScheduling(Process processes[], int n, int time_quantum) {
    // Create a queue to keep track of processes that need to be executed
    int *queue = (int *)malloc(sizeof(int) * 100);
    int front = 0, rear = 0;
    
    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    int current_time = 0;
    int completed = 0;
    
    // Add processes that have arrived at time 0 to the queue
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            queue[rear] = i;
            rear++;
        }
    }
    
    // Execute processes until all are completed
    while (completed != n) {
        // If queue is empty, advance time to next process arrival
        if (front == rear) {
            int next_arrival_time = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].remaining_time > 0 && processes[i].arrival_time > current_time) {
                    if (processes[i].arrival_time < next_arrival_time) {
                        next_arrival_time = processes[i].arrival_time;
                    }
                }
            }
            
            // Update current time
            current_time = next_arrival_time;
            
            // Add processes that have arrived at the new current time
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                    queue[rear] = i;
                    rear++;
                }
            }
            continue;
        }
        
        // Get the front process from queue
        int idx = queue[front];
        front++;
        
        // If process has already completed, skip it
        if (processes[idx].remaining_time == 0) {
            continue;
        }
        
        // Determine how much time this process will run
        int execution_time = (processes[idx].remaining_time < time_quantum) ? 
                              processes[idx].remaining_time : time_quantum;
        
        // Execute the process for the determined time
        processes[idx].remaining_time -= execution_time;
        current_time += execution_time;
        
        // Add processes that arrived during execution
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && 
                processes[i].arrival_time > current_time - execution_time && 
                processes[i].arrival_time <= current_time) {
                queue[rear] = i;
                rear++;
            }
        }
        
        // If process is not completed, add it back to queue
        if (processes[idx].remaining_time > 0) {
            queue[rear] = idx;
            rear++;
        } else {
            // Process is completed
            completed++;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }
    }
    
    free(queue);
}

// Function to calculate and display average waiting and turnaround times
void displayResults(Process processes[], int n) {
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    
    printf("\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", 
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
        
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n, time_quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process *processes = (Process *)malloc(n * sizeof(Process));
    
    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);
    
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        processes[i].id = i + 1;
        
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    roundRobinScheduling(processes, n, time_quantum);
    displayResults(processes, n);
    
    free(processes);
    return 0;
}