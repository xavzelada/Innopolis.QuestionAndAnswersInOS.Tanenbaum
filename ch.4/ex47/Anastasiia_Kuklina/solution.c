#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

double count = 0; // to keep the count of writes


// function which reads from input.txt and writes to output.txt
void rewrite(int* finp, int* fout, int BUFF_SIZE)
{
	char *buff = (char *)malloc(BUFF_SIZE*sizeof(char));

	while(read(*finp, buff, BUFF_SIZE) != 0){

		write(*fout, buff, strlen(buff));
		count++;
	}
}

int main(int argc, char* argv[]){
	
	if(argc == 1){
		printf("Usage: ./solution.c [Buffer size(in bytes)]\n");
		return 0;
	}

	int finp, fout; // input and output file pointers
	finp = open("lorem.txt", O_RDONLY);

	if(finp == -1){
		printf("Error while open input file \n");
		return 0;
	}

	fout = open("output.txt", O_WRONLY);
	
	if(fout == -1){
		printf("Error while open output file\n");
		return 0;
	}

	struct timeval t1, t2; // for capture time

	double elapsedTime;

	// start timer
	gettimeofday(&t1, NULL);

	rewrite(&finp, &fout, atoi(argv[1]));

	// stop timer
	gettimeofday(&t2, NULL);

	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec)*1000.0; // sec to ms

	printf("Overall write time: %lf ms\n", elapsedTime);
	printf("Per write time: %lf ms\n", elapsedTime / count);

	return 0;
}
