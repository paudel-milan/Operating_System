#include<stdio.h>
#include<stdlib.h>


void best_fit(int blockSize[],int processSize[],int n,int m){
    int alloc[m];
    for(int i=0;i<m;i++){
        alloc[i]=-1;
    }
    
    for(int i=0;i<m;i++){
        int bstIdx=-1;
        for(int j=0;j<n;j++){
            if(blockSize[j]>=processSize[i]){
                if(bstIdx==-1){
                    bstIdx=j;
                }else if(blockSize[j]<blockSize[bstIdx]){
                    bstIdx=j;
                }
            }
        }
        
        if(bstIdx!=-1){
            alloc[i]=bstIdx;
            blockSize[bstIdx]-=processSize[i];
        }
    }
    
    printf("ProcessNo   ProcessSize     BlockNo\n");
    for(int i=0;i<m;i++){
        printf("%d       %d       %d\n",i+1,processSize[i],alloc[i]);
    }
    
}

void main(){
    int blockSize[]={100,500,200,300,600};
    int processSize[]={212,417,112,426};
    
    int n=sizeof(blockSize)/sizeof(blockSize[0]);
    int m=sizeof(processSize)/sizeof(processSize[0]);
    
    best_fit(blockSize,processSize,n,m);
}
