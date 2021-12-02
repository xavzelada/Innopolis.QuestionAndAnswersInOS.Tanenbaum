#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128
#define MAX_FILE_NAME 100

// get the number of executable files from data saved in our file
unsigned long get_number_of_lines(FILE* file){
    unsigned long count = 0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file)){
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    }
    return count;
}


// get specific size for some excutable file which saveed in a specific line
char* get_line(int number,FILE* file) {
    char* line;
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        i++;
        if (i == number) {
            printf("%s", line);
            break;
        }
    }
    return line;
}


    int main(int argc, char **argv) {

    //running script to list data of the excuable files and save them in sizes.txt file
    system("./data_generation.sh");
    char number_of_lines_file_name[MAX_FILE_NAME] = "sizes.txt";
    char total_size_file_name[MAX_FILE_NAME] = "total.txt";
    FILE * number_of_line_file = fopen(number_of_lines_file_name,"r");
    FILE * total_size_file = fopen(total_size_file_name,"r");


    if (number_of_line_file == NULL)
    {
        printf("Could not open file %s", number_of_lines_file_name);
        return 0;
    }

    if(total_size_file == NULL){
        printf("Could not open file %s", total_size_file_name);
        return 0;
    }

    double mean,median;
    float total_size;
    char file_buffer [BUF_SIZE + 1];
    fread(file_buffer, sizeof (char), BUF_SIZE, total_size_file);

    sscanf(file_buffer, "%f",&total_size);
    printf("total size = %f\n", total_size );
    unsigned long number_of_executables = get_number_of_lines(number_of_line_file);
    
    // Getting median

    if(number_of_executables % 2 == 0){
        unsigned int first_number = number_of_executables/2;
        unsigned int second_number = first_number+1;

        median = ((int)(get_line(first_number,number_of_line_file)+(int)get_line(second_number,number_of_line_file)))/2;
    }
    else{
        unsigned int number = number_of_executables/2;
        median = (int) get_line(number,number_of_line_file);
    }
    
    // Getting mean of the sizes

    mean = total_size/(double)number_of_executables;

    printf("Mean = %f\n",mean);
    printf("Median = %f\n",median);


    return 0;
}


