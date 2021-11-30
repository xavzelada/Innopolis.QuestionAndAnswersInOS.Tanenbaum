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
    int requests[] = {1, 7 , 15, 2};
    int size  = 4;
    printf("Distance =  %d", FCFS(requests,size));
    return 0;
}
