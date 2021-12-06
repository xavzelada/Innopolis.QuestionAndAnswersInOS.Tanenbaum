#include <stdio.h>
#include <pthread.h>

#define N 15
#define TRUE 1
pthread_cond_t cond_prod, cond_cons;
pthread_mutex_t mutex;

struct product {
    int price;
};

int produced = 0;
struct product products[N];

struct product produce_item() {
    struct product new_prod;
    new_prod.price = 2 * 100 - produced / 5 * 15;
    return new_prod;
}

void consume_product(struct product prod) {
    printf("The price of product #%d, is: %d\n", produced, prod.price);
}

void *producer(void *ptr) {
    while (TRUE) {
        if (produced == N) {
            pthread_cond_wait(&cond_prod, &mutex);
        } else {
            products[produced] = produce_item();
            produced++;
            if (produced == 1) {
                pthread_cond_signal(&cond_cons);
            }
        }
    }
}

void *consumer(void *ptr) {
    while (TRUE) {
        if (produced == 0) {
            pthread_cond_wait(&cond_cons, &mutex);
        } else {
            consume_product(products[produced - 1]);
            produced--;
            if (produced == N - 1) {
                pthread_cond_signal(&cond_prod);
            }
        }
    }
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_cond_init(&cond_prod, NULL);
    pthread_cond_init(&cond_cons, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
}
