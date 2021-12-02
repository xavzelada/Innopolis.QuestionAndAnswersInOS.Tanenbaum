#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

int main() {
    int size;
    printf("Write array size in megabytes: ");
    scanf("%d", &size);

    char *from = (char *) malloc(sizeof(char) * 1024*1024 * size);
    char *to = (char *) malloc(sizeof(char) * 1024*1024 * size);
    memset(from, 'a', 1024 * 1024 * size);
    memset(to, 0, 1024 * 1024 * size);
    clock_t start, end, t;

    start = clock();
    memcpy(to, from, 1024 * 1024 * size);
    t = clock() - start;
    printf ("%f seconds\n",((float)t)/CLOCKS_PER_SEC);

    return 0;
}
