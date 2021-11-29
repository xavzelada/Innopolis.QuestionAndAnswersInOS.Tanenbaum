#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

sem_t s;
bool bowed[2];

void *personThread(int *args) {
    int num = * args;
    while (true) {
        sem_wait(&s);
        if (!bowed[num]) {
            // I'm not bowed. Bow
            bowed[num] = true;
            printf("%d bowed\n", num);
        } else {
            if (bowed[1 - num]) {
                printf("%d raised\n", num);
                sem_post(&s);
                break;
            }
        }
        sem_post(&s);
    }
}

int main() {
    // Init semaphore
    sem_init(&s, 0, 1);
    pthread_t a, b;
    bowed[0] = bowed[1] = false;
    int an = 0;
    int bn = 1;
    pthread_create(&a, NULL, personThread, &an);
    pthread_create(&b, NULL, personThread, &bn);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    return 0;
}





