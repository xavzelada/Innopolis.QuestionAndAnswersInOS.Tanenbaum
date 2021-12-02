#include <stdio.h>
#include <dirent.h>


// print the files in a directory
void printdir(char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (!dir) return;

    entry = readdir(dir);
    printf("\nDirectory %s files:\n====================\n", path);
    while (entry) {
        if(entry->d_name[0] == '.'){
            entry = readdir(dir);
            continue;
        }
        printf("%s\n", entry->d_name);
        entry = readdir(dir);
    }
    closedir(dir);
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++)
        printdir(argv[i]);
    return 0;
}
