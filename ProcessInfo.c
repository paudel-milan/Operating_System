// Lab1: Write a C Program to store and retrieve the Process details such as pid, process name, process arrival time, process completion time, process execution time. Using Dara structures Structure and arrays to demonstrate the above scenario.

#include<stdio.h>
#include<stdlib.h>
#define max 5

typedef struct Process{
    int P_id;
    char P_name[50];
    int P_arrT;
    int P_comT;
    int P_exeT;
}Process;

void insert(Process* arr){
    printf("Enter the process id: ");
    scanf("%d",&arr->P_id);
    printf("Enter the process name: ");
    scanf("%s",&arr->P_name);
    printf("Enter the process arrival time: ");
    scanf("%d",&arr->P_arrT);
    printf("Enter the process execution time: ");
    scanf("%d",&arr->P_exeT);
}

void display(Process arr){
    printf("\nProcess Id: %d",arr.P_id);
    printf("\nProcess Name: %s",arr.P_name);
    printf("\nProcess Arrival time: %d",arr.P_arrT);
    printf("\nProcess Execution time: %d",arr.P_exeT);
    printf("\nProcess Completion time: %d",arr.P_exeT-arr.P_arrT);
}

void search(Process* arr,int id,int n){
    for(int i=0;i<n;i++){
        if(arr[i].P_id==id){
            display(arr[i]);
        }
    }
}


int main(){
    int n,id;
    printf("\nEnter the number of processes: ");
    scanf("%d",&n);

    Process arr[n];

    for(int i=0;i<n;i++){
        insert(&arr[i]);
    }

    printf("Enter the process id to search: ");
    scanf("%d",&id);

    search(arr,id,n);

    
}


