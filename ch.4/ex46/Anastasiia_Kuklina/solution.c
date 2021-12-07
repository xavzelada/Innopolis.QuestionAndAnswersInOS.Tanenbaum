#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/sysmacros.h>


char* concat(char *s1, char *s2) {

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);                      

    char *result = malloc(len1 + len2 + 1);

    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);    

    return result;
}


void printTypeSize(char *path){
    struct stat sb;

    stat(path, &sb);

    switch (sb.st_mode & S_IFMT){
    
        case S_IFSOCK:
            printf("socket\t\t");
            break;
            
        case S_IFLNK:
            printf("symbolic link\t");
            break;
            
        case S_IFREG:
            printf("file\t\t");
            break;
            
        case S_IFBLK:
            printf("block device\t");
            break;
            
        case S_IFDIR:
            printf("directory\t");
            break;
            
        case S_IFCHR:
            printf("character device\t");
            break;

        default:
            printf("other\t\t");
    }   

    printf("%jd bytes\t\t", (intmax_t) sb.st_size);
}

void ls(char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (!dir) return;

    entry = readdir(dir);

    printf("\nIn directory %s files:\n", path);
    printf("\nType\t\t Size \t\t Name\n");
    printf("\n-------------------------------------\n");

    while (entry) {
        
        if(entry->d_name[0] == '.'){
            entry = readdir(dir);
            continue;
        }

        char *s1 = concat(path, "/");
        char *s = concat(s1, entry->d_name);

        printTypeSize(s);
        printf("%s\n", entry->d_name);
        entry = readdir(dir);
    }

    closedir(dir);
}

int main(int argc, char **argv) {

    if (argc == 1)
        ls("./");
    
    else
        for (int i = 1; i < argc; i++)
            ls(argv[i]);

    return 0;
}
