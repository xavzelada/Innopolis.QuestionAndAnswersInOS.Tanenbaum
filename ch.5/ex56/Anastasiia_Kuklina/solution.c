#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true 1
#define false 0
#define disc_size 200


//calculate the distance between two points
int distance(int a, int b){
	return abs(a - b);
}

//first comes first served algorithm
int FCFS(int requests[], int size){
	if (size == 0)
		return 0;

	int distFCFS = 0;

	for (int i = 1; i < size; i++){
		distFCFS += distance(requests[i], requests[i - 1]);
	}
	return distFCFS;
}

//function to decide which request have to go next
int nextIndexSSTF(int requests[], int usedSSTF[], int size, int cInd){
	int next = -1;
	int minD = INT_MAX;

	for (int i = 0; i < size; i++){
		int tempD = distance(requests[cInd], requests[i]);

		if (!usedSSTF[i] && minD > tempD){
			next = i;
			minD = tempD;
		}
	}

	return next;
}

//Shortest Seek Time First
int SSTF(int requests[], int size){
	if (size == 0)
		return 0;

	int distSSTF = 0;
	int cInd = 0;
	int usedSSTF[size];

	usedSSTF[cInd] = true;

	for (int i = 1; i < size; i++){
		usedSSTF[i] = false;
	}

	for (int i = 1; i < size; i++){
		int tempInd = nextIndexSSTF(requests, usedSSTF, size, cInd);

		distSSTF += distance(requests[tempInd], requests[cInd]);

		cInd = tempInd;
		usedSSTF[cInd] = true;
	}

	return distSSTF;
}

//function to decide which request have to go next
int nextIndexCSCAN(int requests[], int usedCSCAN[], int size, int cInd){
	int next = -1;
	int minD = INT_MAX;

	for (int i = 0; i < size; i++){
		int tempD = distance(requests[cInd], requests[i]);

		if (!usedCSCAN[i] && requests[cInd] <= requests[i] && minD > tempD){
			next = i;
			minD = tempD;
		}
	}

	return next;
}


//when we comes to the end of the disc - we have to move to the start
//helps to determine next request after facing the end of the disc
int maxRequestCSCAN(int requests[], int usedCSCAN[], int size, int cInd){
	int next = -1;
		
	for (int i = 0; i < size; i++){
		if (!usedCSCAN[i])
			next = i;
	}

	for (int i = 0; i < size; i++){
		if (!usedCSCAN[i] && requests[next] >= requests[i])
			next = i;
	}

}


//Circular SCAN 
int CSCAN(int requests[], int size){
	if (size == 0)
		return 0;

	int distCSCAN = 0;
	int cInd = 0;
	int usedCSCAN[size];

	usedCSCAN[cInd] = true;

	for (int i = 1; i < size; i++){
		usedCSCAN[i] = false;
	}

	for (int i = 1; i < size; i++){

		int tempInd = nextIndexCSCAN(requests, usedCSCAN, size, cInd);
		
		if (tempInd == -1){
			distCSCAN += distance(requests[cInd], (disc_size - 1));
			tempInd = maxRequestCSCAN(requests, usedCSCAN, size, cInd);

			distCSCAN += distance((disc_size - 1), 0);
			distCSCAN += distance(requests[tempInd], 0);
			i--; 
		}
		else {
			distCSCAN += distance(requests[tempInd], requests[cInd]);
		}
		
		cInd = tempInd;
		usedCSCAN[cInd] = true;
	}

	return distCSCAN;
}
    

int main()
{
	FILE *inp;
    inp = fopen("input.txt", "r");

	// printf("Write the total amount of requests and then each request as integer number\n");
	// printf("Assume that first in the list of requests - is starting position of Read/Write head\n");

	int size = 0;
   	// scanf("%d", &size);
   	fscanf(inp, "%d", &size);
	int requests[size];


    for (int i = 0; i < size; i++){
    	// scanf("%d", &requests[i]);
    	fscanf(inp, "%d", &requests[i]);
    }

    
    printf("FCFS  - Distance =  %d\n", FCFS(requests, size));
    printf("SSTF  - Distance =  %d\n", SSTF(requests, size));
    printf("CSCAN - Distance =  %d\n", CSCAN(requests, size));

    fclose(inp);

    return 0;
}
