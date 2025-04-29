// Write a C program to simulate the following CPU scheduling algorithm to find turnaround time and waiting time.
//a) Round Robin Scheduling Algorithm

#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;      // Process ID
    int at;       // Arrival Time
    int bt;       // Burst Time
    int ct;       // Completion Time
    int wt;       // Waiting Time
    int tat;      // Turnaround Time
    int rem_bt;   // Remaining Burst Time (for RR)
} p;

void insert(p* arr, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &arr[i].pid, &arr[i].at, &arr[i].bt);
        arr[i].rem_bt = arr[i].bt;  // Initialize remaining burst time
    }
}

void findCt(p* arr, int n, int quantum) {
    int currentTime = 0;
    int completed = 0;

    // Check if any process is pending and needs to be processed
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (arr[i].at <= currentTime && arr[i].rem_bt > 0) {
                if (arr[i].rem_bt <= quantum) {
                    currentTime += arr[i].rem_bt;
                    arr[i].rem_bt = 0;
                    arr[i].ct = currentTime;
                    completed++;
                } else {
                    arr[i].rem_bt -= quantum;
                    currentTime += quantum;
                }
            }
        }
    }
}

void findTAT(p* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i].tat = arr[i].ct - arr[i].at; 
    }
}

void findWT(p* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i].wt = arr[i].tat - arr[i].bt; 
    }
}

void findAVG(p* arr, int n) {
    double TATavg = 0, WTavg = 0;

    findCt(arr, n, 4); // Assuming a time quantum of 4 units
    findTAT(arr, n);
    findWT(arr, n);

    // Display results
    printf("\nProcess Information: \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].ct, arr[i].tat, arr[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", TATavg / n);
    printf("Average Waiting Time: %.2f\n", WTavg / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    p *arr = (p *)malloc(n * sizeof(p)); // Dynamically allocate memory for processes

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter Process ID, Arrival Time, and Burst Time for Processes: ");
    insert(arr, n);

    findAVG(arr, n);

    free(arr); // Free dynamically allocated memory
    return 0;
}

