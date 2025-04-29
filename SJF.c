// Write a C program to simulate the following CPU scheduling algorithm to find turnaround time and waiting time.
//a) SJF

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10

typedef struct Process {
    int pid, at, bt, ct, wt, tat;
} p;

void insert(p* arr, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &arr[i].pid, &arr[i].at, &arr[i].bt);
    }
}

void sort(p* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].at > arr[j].at) {
                p temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void findCt(p* arr, int n) {
    int currentTime = 0, completed = 0;
    
    while (completed < n) {
        int minBt = INT_MAX, minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (arr[i].at <= currentTime && arr[i].ct == 0 && arr[i].bt < minBt) {
                minBt = arr[i].bt;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime = arr[0].at;  
        } else {
            arr[minIndex].ct = currentTime + arr[minIndex].bt;
            currentTime = arr[minIndex].ct;
            arr[minIndex].tat = arr[minIndex].ct - arr[minIndex].at;
            arr[minIndex].wt = arr[minIndex].tat - arr[minIndex].bt;
            completed++;
        }
    }
}

void findAVG(p* arr, int n) {
    double TATavg = 0, WTavg = 0;

    sort(arr, n);
    findCt(arr, n);

    for (int i = 0; i < n; i++) {
        TATavg += arr[i].tat;
        WTavg += arr[i].wt;
    }

    printf("Process Information:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].ct, arr[i].tat, arr[i].wt);
    }

    printf("Avg TAT: %.2f\n", TATavg / n);
    printf("Avg WT: %.2f\n", WTavg / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    p arr[n];
    printf("Enter PID, AT, BT for each process:\n");
    insert(arr, n);

    findAVG(arr, n);

    return 0;
}
