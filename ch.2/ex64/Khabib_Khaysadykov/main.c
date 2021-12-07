#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

int N, P;
pthread_mutex_t mutex;
int fsum = 0;

void *worker(void *args) {
    int i = (int)(uintptr_t)args;
    for (int j = i; j * j <= N; j += P) {
        if (N % j == 0) {
            pthread_mutex_lock(&mutex);
            printf("Factor %d was found in the thread %d\n", j, i);
            fsum += j + N / j;
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main() {
    printf("Enter numbers:\n");
    scanf("%d%d", &N, &P);
    fsum = -N;
    pthread_t threads[P];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < P; ++i) pthread_create(&threads[i], NULL, worker, (void *)(uintptr_t)(i + 1));
    for (int i = 0; i < P; ++i) pthread_join(threads[i], NULL);

    printf("Sum: %d\n", fsum);
    if (N == fsum) printf("TRUE\n");
    else printf("FALSE\n");
}