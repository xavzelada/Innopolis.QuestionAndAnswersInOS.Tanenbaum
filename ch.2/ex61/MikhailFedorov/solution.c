#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define N 3

int *turn; // shared variable

void critical_region(int i) {
    printf("I'm in the critical region! My index: %d", i);
}

void noncritical_region(int i) {
    printf("I'm no more in the critical region! My index: %d", i);
}

void work(int i) {
    while (*turn != i);
    critical_region(i);
    *turn = (i + 1) % N;
    noncritical_region(i);
}

int main() {
    turn = mmap(turn, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,
                0); // Mapping shared variable
    *turn = 0;
    for (int i = 0; i < N; ++i) {
        if (fork() != 0) {
            work(i);
            exit(0);
        }
    }
    while (wait(NULL) > 0); // Waiting for all children to finish
    munmap(turn, sizeof(int)); // Unmapping shared variable
    return 0;
}
