#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define N 3
#define TRUE 1

int *turn;

void work(int i)
{
    while(TRUE){
        while(*turn != i);
        critical_region(i);

        *turn = (i + 1) % N;
        noncritical_region(i);
    }
}

void noncritical_region(int i)
{
    printf("%i entered noncritical region\n", i);
    sleep(1);
    printf("%i left noncritical region\n", i);
}

void critical_region(int i)
{
    printf("%i entered critical region\n", i);
    sleep(1);
    printf("%i left critical region\n", i);
}


int main(void)
{
    turn = mmap(turn, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *turn = 0;
    int i;

    for(i = 0; i < N; ++i){
        if(!fork()){
            work(i);
            exit(0);
        }
    }

    while(wait(NULL) > 0);

    munmap(turn, sizeof(int));
    return 0;
}