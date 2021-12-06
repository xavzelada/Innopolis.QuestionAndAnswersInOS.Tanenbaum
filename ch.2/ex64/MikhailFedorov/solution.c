#include <stdio.h>
#include <pthread.h>

int N, P;
pthread_mutex_t sum_mutex;
int factors_sum = 0;

void *worker(void *args) {
    int index = (int) args;
    for (int i = index; i * i <= N; i += P) {
        if (N % i == 0) {
            pthread_mutex_lock(&sum_mutex);
            printf("Found factor %d in thread %d\n", i, index);
            factors_sum += i + N / i;
            pthread_mutex_unlock(&sum_mutex);
        }
    }
}

int main() {
    scanf("%d%d", &N, &P);
    factors_sum = -N;
    pthread_t threads[P];
    pthread_mutex_init(&sum_mutex, NULL);
    for (int i = 0; i < P; ++i) {
        pthread_create(&threads[i], NULL, worker, (void *) (i + 1));
    }
    for (int i = 0; i < P; ++i) {
        pthread_join(threads[i], NULL);
    }
    printf("Sum: %d\n", factors_sum);
    if (N == factors_sum) {
        printf("%d is a perfect number!\n", N);
    } else {
        printf("%d is not a perfect number!\n", N);
    }
}
