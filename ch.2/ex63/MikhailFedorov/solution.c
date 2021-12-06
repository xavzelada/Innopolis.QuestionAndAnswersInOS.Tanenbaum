#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int N;
int segs = 5;
int instance_index;

int prime(int a) {
    if (a == 1) {
        return 0;
    }
    for (int i = 2; i * i <= a; ++i) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}

int create_instance(int num) {
    int id = fork();
    if (id == 0) {
        instance_index = num;
    }
    return id;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    instance_index = 0;
    int a[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < segs; ++i) {
        int id = create_instance(i);
        if (id == 0) {
            break;
        }
    }
    for (int i = instance_index; i < N; i += segs) {
        printf("Instance number: %d, checking for primarity: %d, result is: %d\n", instance_index, a[i], prime(a[i]));
    }
    while (wait(NULL) > 0);
}
