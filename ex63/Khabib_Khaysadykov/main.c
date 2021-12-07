#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int idOfInstance;
int n;
int s = 5;

int create(int n) {
    int id = fork();
    if (id == 0) idOfInstance = n;
    return id;
}

int prime(int a) {
    if (a == 1) return 0;
    for (int i = 2; i * i <= a; ++i) if (a % i == 0) return 0;
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    idOfInstance = 0;
    int a[n];
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i < s; ++i) {
        int id = create(i);
        if (id == 0)break;
    }
    for (int i = idOfInstance; i < n; i += s) {
        printf("Number of intance is   - [%d]\n", idOfInstance);
        printf("Checking for primarity - [%d]\n",a[i]);
        printf("Result                 - [%d]\n\n\n", prime(a[i]));
    }
    while (wait(NULL) > 0);
}
