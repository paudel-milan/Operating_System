#include <stdio.h>
#define N 5     // Number of processes
#define M 3     // Number of resources

int finish[N] = {0};

int isSafe(int alloc[N][M], int max[N][M], int avail[M]) {
    int work[M];
    for (int i = 0; i < M; i++)
        work[i] = avail[i];

    int safeseq[N], count = 0;

    while (count < N) {
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < M; j++)
                    if (max[i][j] - alloc[i][j] > work[j])
                        break;

                if (j == M) {
                    for (int k = 0; k < M; k++)
                        work[k] += alloc[i][k];

                    safeseq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < N; i++)
        printf("P%d ", safeseq[i]);
    printf("\n");
    return 1;
}3 3 2

int main() {
    int alloc[N][M], max[N][M], avail[M];

    printf("Enter Allocation Matrix (%dx%d):\n", N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix (%dx%d):\n", N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources (%d):\n", M);
    for (int i = 0; i < M; i++)
        scanf("%d", &avail[i]);

    isSafe(alloc, max, avail);

    return 0;
}
