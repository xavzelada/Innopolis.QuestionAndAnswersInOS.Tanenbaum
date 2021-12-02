#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_NAME 2048
#define MAX_FILES 100000
#define MOD 10007

// a stucture containing the files with specific link
struct link {
    char filenames[MAX_FILES][MAX_NAME];
    int file_count;
};


int file_count = 0;
struct link *links[MAX_FILES];


// recursively scanning directory
void scanDir(const char *name) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        char path[MAX_NAME];
        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            scanDir(path);
        } else {
            struct stat s = {};
            if (stat(path, &s) != 0) {
                // printf("Error reading file stat\n");
                break;
            }
            if (s.st_nlink >= 2) {
                file_count++;
                if (links[s.st_ino % MOD] == NULL) {
                    links[s.st_ino % MOD] = malloc(sizeof(struct link));
                    strncpy(links[s.st_ino % MOD]->filenames[0], path, MAX_NAME);
                    links[s.st_ino % MOD]->file_count = 1;
                } else {
                    strncpy(links[s.st_ino % MOD]->filenames[links[s.st_ino % MOD]->file_count++], path, MAX_NAME);
                }
            }
        }
    }
    closedir(dir);
}


int main() {
    scanDir("/");
    printf("Found %d files with equal to or more than 2 hard links:\n", file_count);
    //finding files with more than or equal 2 hard links
    for (int i = 0; i < 100000; i++) {
        if (links[i] == NULL) continue;
        printf("I-node: %d (%d files)\n", i, links[i]->file_count);
        for (int j = 0; j < links[i]->file_count; j++) {
            printf("\t%s\n", links[i]->filenames[j]);
        }
        printf("\n");
    }
    return 0;

}
