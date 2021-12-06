#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define PERSON_AMOUNT 10
pthread_mutex_t mutex;
pthread_cond_t cond_no_women, cond_no_men;
// 0 - Empty
// negative integer - Women present
// positive integer - Men present
int state = 0;
//woman_wants_to_enter, man_wants_to_enter,
//woman_leaves, man_leaves

void woman_wants_to_enter() {
    while (TRUE) {
        pthread_mutex_lock(&mutex);
        if (state > 0) {
            pthread_cond_wait(&cond_no_men, &mutex);
        } else {
            state--;
            printf("Woman entered\n");
        }
        pthread_mutex_unlock(&mutex);
    }
};

void woman_leaves() {
    pthread_mutex_lock(&mutex);
    state++;
    printf("Woman exited\n");
    if (state == 0) {
        pthread_cond_signal(&cond_no_women);
        pthread_cond_signal(&cond_no_men);
    }
    pthread_mutex_unlock(&mutex);
};

void man_wants_to_enter() {
    while (TRUE) {
        pthread_mutex_lock(&mutex);
        if (state < 0) {
            pthread_cond_wait(&cond_no_women, &mutex);
        } else {
            state++;
            printf("Man entered\n");
        }
        pthread_mutex_unlock(&mutex);
    }
};

void man_leaves() {
    pthread_mutex_lock(&mutex);
    state--;
    printf("Man exited\n");
    if (state == 0) {
        printf("Bathroom is free\n");
        pthread_cond_signal(&cond_no_women);
        pthread_cond_signal(&cond_no_men);
    }
    pthread_mutex_unlock(&mutex);
};


void *women(void *ptr) {
    woman_wants_to_enter();
    sleep(10);
    woman_leaves();
}

void *men(void *ptr) {
    man_wants_to_enter();
    sleep(10);
    man_leaves();
}


int main() {
    pthread_t threads[PERSON_AMOUNT];
    time_t t;
    srand((unsigned) time(&t));
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_no_men, NULL);
    pthread_cond_init(&cond_no_women, NULL);
    for (int i = 0; i < PERSON_AMOUNT; i++) {
        // 50% for person to be a man
        if (rand() % 2) {
            pthread_create(&threads[i], NULL, men, NULL);
        } else {
            pthread_create(&threads[i], NULL, women, NULL);
        }
    }

    for (int i = 0; i < PERSON_AMOUNT; i++) {
        pthread_join(threads[i], NULL);
    }
}
