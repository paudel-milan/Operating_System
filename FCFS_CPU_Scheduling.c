// Write a C program to simulate the following CPU scheduling algorithm to find turnaround time and waiting time.
// a) FCFS b) SJF c) Priority d) Round Robin (Experiment with different quantum sizes for RR algorithm)

#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int pid;
    int at;
    int ct;
    int bt;
    int wt;
    int tat;
}p;

void insert(p* arr,int n){
    for(int i=0;i<n;i++){
        scanf("%d %d %d",&arr[i].pid,&arr[i].at,&arr[i].bt);
    }
}

void findCt(p* arr,int n){
    if(arr[0].at==0){
        arr[0].ct=arr[0].bt;
    }
    else{
        arr[0].ct=arr[0].bt-arr[0].at;
    }

    for(int i=1;i<n;i++){
        if(arr[i].at>arr[i-1].ct){
            arr[i].ct=arr[i].at+arr[i].bt;
        }
        else{
            arr[i].ct=arr[i-1].ct+arr[i].bt;
        }
    }
}

void findTAT(p* arr, int n){
    for(int i=0;i<n;i++){
        arr[i].tat=arr[i].ct-arr[i].at;
    }
}

void findWT(p* arr, int n){
    for(int i=0;i<n;i++){
        arr[i].wt=arr[i].tat-arr[i].bt;
    }
}

void findAVG(p* arr,int n){
    double TATavg=0;
    double WTavg=0;

    findCt(arr,n);
    findTAT(arr,n);
    findWT(arr,n);

    for(int i=0;i<n;i++){
        TATavg+=arr[i].tat;
        WTavg+=arr[i].wt;
    }

    //display
    printf("Process Information: \n");
    printf("Process ID\t Arrival Time\t Burst Time\t Completion Time\t Turn Around Time\t Waiting Time\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",arr[i].pid,arr[i].at,arr[i].bt,arr[i].ct,arr[i].tat,arr[i].wt);
    }

    printf("Averrage Turn Around Time: %d\n",TATavg/n);
    printf("Average Waiting Time: %d\n",WTavg/n);
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    p arr[n];

    printf("Enter the Process id, arrival time, burst time for n processes: ");
    insert(arr,n);

    findAVG(arr,n);
}