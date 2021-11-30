#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int iterativeBinarySearch(int array[], int start_index, int end_index, int element){
    while (start_index <= end_index){
        int middle = start_index + (end_index- start_index )/2;
        if (array[middle] == element)
            return middle;
        if (array[middle] < element)
            start_index = middle + 1;
        else
            end_index = middle - 1;
    }
    return -1;
}

int elevator(int requests[], int size,int init_index) {
    int distance = 0;
    bool up = true;
    int index_to_right = init_index;
    int index_to_left = init_index - 1;

    while(up){
        if(index_to_right + 1 <  size){
            distance += abs(requests[index_to_right+1] - requests[index_to_right]);
            index_to_right++;
            continue;
        }
        up = false;
    }

    distance+= abs(requests[index_to_left] - requests[index_to_right]);

    while(!up){
        if(index_to_left > 0){
            distance+= abs(requests[index_to_left - 1] - requests[index_to_left]);
            index_to_left--;
            continue;
        }
        up = true;
    }

    return distance;
}

int main() {
    int requests[] = {11, 1, 36, 16, 34, 9, 12};
    int size = 7;
    qsort(requests, size, sizeof(int), cmpfunc);
    int index = iterativeBinarySearch(requests,0,6,11);

    printf("Distance =  %d", elevator(requests, size, index));
    return 0;
}


