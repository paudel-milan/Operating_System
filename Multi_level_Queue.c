#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;    
    int at;     
    int bt;    
    int ct;     
    int wt;     
    int tat;                                                                                                                                                                                                                                                                                                             
    int process; 
} p;

void insert(p* arr, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &arr[i].pid, &arr[i].at, &arr[i].bt, &arr[i].process);
    }
}

void sort(p* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].at > arr[j].at || (arr[i].at == arr[j].at && arr[i].process > arr[j].process)) {
                p temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;                                                              
            }
        }
    }
}

void findCt(p* arr,int n){
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int minPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (arr[i].at <= currentTime && arr[i].ct == 0) {
                if (arr[i].process < minPriority) {
                    minPriority = arr[i].process;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime = arr[0].at;
        } else {
            arr[idx].ct = currentTime + arr[idx].bt; 
            currentTime = arr[idx].ct; 
            completed++;
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

    findCt(arr, n);
    findTAT(arr, n);
    findWT(arr, n);

    for (int i = 0; i < n; i++) {
        TATavg += arr[i].tat;
        WTavg += arr[i].wt;
    }

    // Display results
    printf("\nProcess Information: \n");
    printf("PID\tAT\tBT\tProcess Queue\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].process, arr[i].ct, arr[i].tat, arr[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", TATavg / n);
    printf("Average Waiting Time: %.2f\n", WTavg / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    p *arr = (p *)malloc(n * sizeof(p)); 
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter Process ID, Arrival Time, Burst Time, and Process(1 for System Process and 2 for User Process):\n ");
    insert(arr, n);

    sort(arr, n);

    findAVG(arr, n);

    free(arr); 
    return 0;
}
