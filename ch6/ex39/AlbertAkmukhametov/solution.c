#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BABOON_COUNT 100

typedef struct baboonCreationArgs {
    bool eastward;
    int id;
} BaboonArgs_t;

typedef enum {
    EASTWARD,
    WESTWARD,
    NONE
} direction;

direction dir = NONE;
int onBridge = 0;
sem_t bridge;

void *baboonFunction(void *pargs) {
    BaboonArgs_t *args = (BaboonArgs_t *) pargs;
    printf("Baboon %d wanna move %s\n", args->id, args->eastward ? "eastward" : "westward");

    if (args->eastward) {
        // First, wait when bridge became free or in our direction
        while (1) {
            sem_wait(&bridge);
            if (dir == WESTWARD && onBridge > 0) {
                sem_post(&bridge);
                continue;
            }
            dir = EASTWARD;
            onBridge++;
            sem_post(&bridge);
            break;
        }
    } else {
        while (1) {
            sem_wait(&bridge);
            if (dir == EASTWARD && onBridge > 0) {
                sem_post(&bridge);
                continue;
            }
            dir = WESTWARD;
            onBridge++;
            sem_post(&bridge);
            break;
        }
    }

    printf("Baboon %d entered the bridge\n", args->id);

    sleep(5);
    sem_wait(&bridge);
    onBridge--;
    sem_post(&bridge);

    printf("Baboon %d left the bridge\n", args->id);
    free(pargs);
}

int main() {
    srand(time(NULL));
    pthread_t *tids = malloc(sizeof(tids) * BABOON_COUNT);

    sem_init(&bridge, 1, 1);

    for (int i = 0; i < BABOON_COUNT; i++) {
        BaboonArgs_t *args = (BaboonArgs_t *) malloc(sizeof(BaboonArgs_t));
        args->eastward = rand() > RAND_MAX / 2;
        args->id = i;

        pthread_create(tids + i, NULL, baboonFunction, (void *) args);
        sleep(rand() % 5);
    }
    return 0;
}

