#include <stdio.h>
#include <stdlib.h>


int minimum_distance_index(int diff[][2], int n) {
    int index = -1;
    int minimum = (int) 1e9;

    for (int i = 0; i < n; i++) {
        if (!diff[i][1] && minimum > diff[i][0]) {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

void SSTF(int request[], int init_request, int n) {
    if (!n) return;
    int diff[n][2], distance = 0;

    for (int i = 0; i < n; i++) {
        diff[i][0] = diff[i][1] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            diff[j][0] = abs(init_request - request[j]);
        }
        int index = minimum_distance_index(diff, n);
        diff[index][1] = 1;
        distance += diff[index][0];
        init_request = request[index];
    }
    printf("Distance = %d\n", distance);
}

int main() {
    int requests[] = {11, 1, 36, 16, 34, 9, 12};
    int n = sizeof(requests) / sizeof(int);
    SSTF(requests, requests[0], n);

    return 0;
}



