#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define LEN 5

typedef struct {
    int buf[LEN]; 
    size_t len; 

    pthread_mutex_t mutex; 
    pthread_cond_t cond_produce; 
    pthread_cond_t cond_consume; 
} buffer_t;


void* con(void *arg) {
    buffer_t *buf = (buffer_t*)arg;

    while(1) {
    #ifdef OVERFLOW
        sleep(rand() % 3);
    #endif
        pthread_mutex_lock(&buf->mutex);

        if(buf->len == 0) pthread_cond_wait(&buf->cond_consume, &buf->mutex);
        --buf->len;
        printf("The consumer take: %d\n", buf->buf[buf->len]);
        pthread_cond_signal(&buf->cond_produce);
        pthread_mutex_unlock(&buf->mutex);
    }
    return NULL;
}

void* pro(void *arg) {
    buffer_t *buf = (buffer_t*)arg;

    while(1) {
      #ifdef UNDERFLOW
        sleep(rand() % 3);
      #endif
        pthread_mutex_lock(&buf->mutex);
        if(buf->len == LEN) pthread_cond_wait(&buf->cond_produce, &buf->mutex);
        int t = rand();
        printf("The producer create: %d\n", t);
        buf->buf[buf->len] = t;
        ++buf->len;
        pthread_cond_signal(&buf->cond_consume);
        pthread_mutex_unlock(&buf->mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    buffer_t buf = {
        .len = 0,
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .cond_produce = PTHREAD_COND_INITIALIZER,
        .cond_consume = PTHREAD_COND_INITIALIZER
    };
    pthread_t p, c;
    pthread_create(&p, NULL, pro, (void*)&buf);
    pthread_create(&c, NULL, con, (void*)&buf);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}