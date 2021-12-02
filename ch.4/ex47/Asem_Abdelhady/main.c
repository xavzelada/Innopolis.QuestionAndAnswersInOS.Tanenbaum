#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include <string.h>


//reading a file with some butter size
void read_file(char *filename, const int BUF_SIZE) {
    char source[BUF_SIZE + 1];
    FILE *fp = fopen(filename, "rb");
    size_t n = 1;
    while (n) {
        n = fread(source, sizeof(char), BUF_SIZE, fp);
    }
    fclose(fp);
}


//writting into a file with some buffer size
void write_file(char *filename, const int BUF_SIZE) {
    FILE *fp = fopen(filename, "w");

    char *str = malloc(BUF_SIZE + 1);
    memset(str, 'a', BUF_SIZE);
    str[BUF_SIZE] = 0;

    for (int i = 0; i < (2LL * 1024 * 1024 * 1024) / BUF_SIZE; i++) {
        fwrite(str, sizeof(char), BUF_SIZE, fp);
    }
    fclose(fp);
}


int main() {
    for (int buf_size = 64; buf_size < 4 * 1024; buf_size += 1024) {
        clock_t t;
        t = clock();
        //reading the file inside same directory as the exutable which size is 2GB or more
        read_file("./file.txt", buf_size);
        t = clock() - t;
        double read_time = ((double) t) / CLOCKS_PER_SEC;

        t = clock();
        //writing to a file inside same directory as the exutable which size is 2GB or more
        write_file("./file2.txt", buf_size);
        t = clock() - t;
        double write_time = ((double) t) / CLOCKS_PER_SEC;

	//Read and write time for the bigger buffer size is better
        printf("Buf_size: %d\t\tRead time: %f\t Write time: %f\n", buf_size, read_time, write_time);
    }
}
