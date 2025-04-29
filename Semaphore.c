#include<stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include<stdlib.h>

#define max 10
int in=0,out=0;
int s=1;
int full=0;
int empty=max;
int buffer[max];


void mywait(int *s){
    while(*s<=0);
    (*s)--;
}

void mysignal(int *s){
    (*s)++;
}

void *producer(){
    while(1){
        int item=rand()%100;
        mywait(&empty);
        mywait(&s);

        buffer[in]=item;
        printf("Producer produced item: %d\n",item);
        in=(in+1)%max;

        mysignal(&s);
        mysignal(&full);

        sleep(1);
    }

}

void *consumer(){
    while(1){
        mywait(&full);
        mywait(&s);
                                
        int item=buffer[out];
        printf("Consumer consumed item: %d\n",item);
        out=(out+1)%max;

        mysignal(&s);
        mysignal(&empty);

        sleep(2);
    }
}


void main(){
    // for(int i=0;i<max;i++){
    //     producer();
    //     consumer();
    // }

    pthread_t prodThread, consThread;

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);


    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);
}