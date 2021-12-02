#include <stdio.h>
#include <stdlib.h>

int FCFS(int requests[], int size){
    int distance  = 0;
    for(int i = 0; i < size - 1; i++){
        distance+=abs(requests[i+1] - requests[i]);
    }
    return distance;
}

int main()
{
    int requests[] = {11, 1, 36, 16, 34, 9, 12};
    int size  = 7;
    printf("Distance =  %d\n", FCFS(requests,size));
    return 0;
}
