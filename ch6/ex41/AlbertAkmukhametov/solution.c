#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ask(char *str, int *var) {
    printf("%s: ", str);
    scanf("%d", var);
}

int main() {
    int pCount, rCount;
    ask("Enter the number of resource types", &rCount);
    ask("Enter the number of clients", &pCount);

    int *available = (int *) malloc(sizeof(int) * rCount);
    for (int i = 0; i < rCount; i++) {
        printf("Enter the number of instances of type %d: ", i);
        scanf("%d", available + i);
    }

    int **allocated = (int **) malloc(sizeof(int *) * pCount);
    for (int i = 0; i < pCount; i++) {
        allocated[i] = (int *) malloc(sizeof(int) * rCount);
        printf("Enter the numbers of resource instanecs allocated to client %d\n", i);
        for (int j = 0; j < rCount; j++) {
            scanf("%d", allocated[i] + j);
            available[j] -= allocated[i][j];
        }
    }

    int **required = (int **) malloc(sizeof(int *) * pCount);
    for (int i = 0; i < pCount; i++) {
        required[i] = (int *) malloc(sizeof(int) * rCount);
        printf("Enter the numbers of resource instanecs required by client %d\n", i);
        for (int j = 0; j < rCount; j++)
            scanf("%d", required[i] + j);
    }

    bool *isClosed = (bool *) malloc(sizeof(bool) * pCount);
    memset(isClosed, 0, sizeof(bool) * pCount);

    int requestsRemain = pCount;
    bool stuck;
    while (requestsRemain != 0) {
        stuck = true;
        for (int i = 0; i < pCount; i++) {
            if (isClosed[i])
                continue;
            bool satisfied = true;
            for (int j = 0; satisfied && j < rCount; j++) {
                if (available[j] < required[i][j])
                    satisfied = false;
            }

            if (!satisfied)
                continue;

            for (int j = 0; j < rCount; j++)
                available[j] += allocated[i][j];
            isClosed[i] = true;
            stuck = false;
            required--;
        }
        if (stuck)
            break;
    }

    printf("State will be %s\n", stuck ? "unsafe" : "safe");
    
    free(available);
    free(isClosed);
    for (int i = 0; i < pCount; i++) {
        free(required[i]);
        free(allocated[i]);
    }
    free(required);
    free(allocated);
}

