#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + N - 1) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
int forks[N]; 

void mywait(int *s) {
    while (*s <= 0);
    (*s)--;
}

void mysignal(int *s) {
    (*s)++;
}

void take_fork(int phnum) {
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);

    while (1) {
        if (forks[LEFT] && forks[phnum]) { 
            mywait(&forks[LEFT]);
            mywait(&forks[phnum]);
            state[phnum] = EATING;
            printf("Philosopher %d takes fork %d and %d\n",
                   phnum + 1, LEFT + 1, phnum + 1);
            printf("Philosopher %d is Eating\n", phnum + 1);
            break;
        }
        usleep(1000);
    }
}

void put_fork(int phnum) {
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n",
           phnum + 1, LEFT + 1, phnum + 1);
    mysignal(&forks[LEFT]);
    mysignal(&forks[phnum]);
    printf("Philosopher %d is thinking\n", phnum + 1);
}

void *philosopher(void *num) {
    int *i = num;
    while (1) {
        sleep(rand() % 3); 
        take_fork(*i);
        sleep(rand() % 3); 
        put_fork(*i);
    }
}

int main() {
    pthread_t thread_id[N];
    int i;

    for (i = 0; i < N; i++) {
        forks[i] = 1;
    }

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    sleep(10);


    for (i = 0; i < N; i++) {
        pthread_cancel(thread_id[i]);
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}