#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    // Read number of prcoesses and resources
    int PROC_CNT, RES_TYPES;
    scanf("%d %d", PROC_CNT, RES_TYPES);
    
    // Resources in existance
    int *e = (int *) malloc(sizeof(int) * RES_TYPES);
    for (int i = 0; i < RES_TYPES; i++)
        scanf("%d ", e + i);
    // Resources available
    int *a = (int *) malloc(sizeof(int) * RES_TYPES);
    for (int i = 0; i < RES_TYPES; i++)
        scanf("%d ", a + i);

    // Allocation matrix
    int **c = (int **) malloc(sizeof(int *) * PROC_CNT);
    for (int i = 0; i < PROC_CNT; i++) {
        c[i] = (int *) malloc(sizeof(int) * RES_TYPES);
        for (int j = 0; j < RES_TYPES; j++)
            scanf("%d ", c[i] + j);
    }

    // Request matrix
    int **r = (int **) malloc(sizeof(int *) * PROC_CNT);
    for (int i = 0; i < PROC_CNT; i++) {
        r[i] = (int *) malloc(sizeof(int) * RES_TYPES);
        for (int j = 0; j < RES_TYPES; j++)
            scanf("%d ", r[i] + j);
    }

    int* isEnded = (int*) malloc(sizeof(int) * PROC_CNT);
    int endedCnt = 0;
    memset(isEnded, 0, PROC_CNT * sizeof(int));

    int flag = 1;
    while (flag) {
        flag = 0;
        for (int pid = 0; pid < PROC_CNT; pid++) {
            if (isEnded[pid] == 1)
                continue;

            int less = 1;
            for (int res = 0; less && res < RES_TYPES; res++)
                if (r[pid][res] - c[pid][res] > a[res])
                    less = 0;

            if (!less)
                continue;

            flag = 1;
            isEnded[pid] = 1;
            endedCnt++;
            for (int res = 0; res < RES_TYPES; res++)
                a[res] += c[pid][res];

        }
    }

    if (endedCnt == PROC_CNT) {
        printf("No deadlocks!");
        exit(0);
    }

    printf("Potential deadlock process: ");
    for (int i = 0; i < PROC_CNT; i++)
        if (!isEnded[i])
            printf("%d ", i);
}




