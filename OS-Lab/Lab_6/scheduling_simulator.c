#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining time (for SRTN and RR)
    int start;      // Start time
    int finish;     // Finish time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
} Process;

void fcfs(Process processes[], int n);
void sjf(Process processes[], int n);
void srtn(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);
void calculate_times(Process processes[], int n);
void display_results(Process processes[], int n);
void reset_processes(Process processes[], int n);

int main() {
    Process processes[MAX_PROCESSES];
    int n, choice, quantum;
    
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
        processes[i].remaining = processes[i].burst;
    }
    
    do {
        printf("\nCPU Scheduling Algorithms\n");
        printf("1. FCFS (First Come First Serve)\n");
        printf("2. SJF (Shortest Job First)\n");
        printf("3. SRTN (Shortest Remaining Time Next)\n");
        printf("4. Round Robin\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        reset_processes(processes, n);
        
        switch (choice) {
            case 1:
                fcfs(processes, n);
                break;
            case 2:
                sjf(processes, n);
                break;
            case 3:
                srtn(processes, n);
                break;
            case 4:
                printf("Enter time quantum for Round Robin: ");
                scanf("%d", &quantum);
                round_robin(processes, n, quantum);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    
    return 0;
}

void reset_processes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
        processes[i].start = -1;
        processes[i].finish = -1;
        processes[i].waiting = -1;
        processes[i].turnaround = -1;
    }
}

void calculate_times(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].finish - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
    }
}

void display_results(Process processes[], int n) {
    float avg_waiting = 0, avg_turnaround = 0;
    
    printf("\nPID\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival,
               processes[i].burst,
               processes[i].start,
               processes[i].finish,
               processes[i].waiting,
               processes[i].turnaround);
        
        avg_waiting += processes[i].waiting;
        avg_turnaround += processes[i].turnaround;
    }
    
    avg_waiting /= n;
    avg_turnaround /= n;
    
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);
}

void fcfs(Process processes[], int n) {
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival) {
            current_time = processes[i].arrival;
        }
        processes[i].start = current_time;
        processes[i].finish = current_time + processes[i].burst;
        current_time = processes[i].finish;
    }
    
    calculate_times(processes, n);
    display_results(processes, n);
}

void sjf(Process processes[], int n) {
    int completed = 0;
    int current_time = 0;
    
    while (completed < n) {
        int shortest = -1;
        int shortest_burst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && 
                processes[i].remaining > 0 && 
                processes[i].remaining < shortest_burst) {
                shortest = i;
                shortest_burst = processes[i].remaining;
            }
        }
        
        if (shortest == -1) {
            current_time++;
            continue;
        }
        
        if (processes[shortest].start == -1) {
            processes[shortest].start = current_time;
        }
        
        processes[shortest].remaining--;
        current_time++;
        
        if (processes[shortest].remaining == 0) {
            processes[shortest].finish = current_time;
            completed++;
        }
    }
    
    calculate_times(processes, n);
    display_results(processes, n);
}

void srtn(Process processes[], int n) {
    int completed = 0;
    int current_time = 0;
    
    while (completed < n) {
        int shortest = -1;
        int shortest_burst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && 
                processes[i].remaining > 0 && 
                processes[i].remaining < shortest_burst) {
                shortest = i;
                shortest_burst = processes[i].remaining;
            }
        }
        
        if (shortest == -1) {
            current_time++;
            continue;
        }
        
        if (processes[shortest].start == -1) {
            processes[shortest].start = current_time;
        }
        
        processes[shortest].remaining--;
        current_time++;
        
        if (processes[shortest].remaining == 0) {
            processes[shortest].finish = current_time;
            completed++;
        }
    }
    
    calculate_times(processes, n);
    display_results(processes, n);
}

void round_robin(Process processes[], int n, int quantum) {
    int completed = 0;
    int current_time = 0;
    int *remaining = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        remaining[i] = processes[i].burst;
    }
    
    while (completed < n) {
        bool any_executed = false;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && remaining[i] > 0) {
                any_executed = true;
                
                if (processes[i].start == -1) {
                    processes[i].start = current_time;
                }
                
                if (remaining[i] > quantum) {
                    current_time += quantum;
                    remaining[i] -= quantum;
                } else {
                    current_time += remaining[i];
                    remaining[i] = 0;
                    processes[i].finish = current_time;
                    completed++;
                }
            }
        }
        
        if (!any_executed) {
            current_time++;
        }
    }
    
    calculate_times(processes, n);
    display_results(processes, n);
    free(remaining);
}
