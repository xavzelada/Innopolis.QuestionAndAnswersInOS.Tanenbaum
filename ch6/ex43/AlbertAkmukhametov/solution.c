#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int len;
    int *c;
} arr_t;

void add(arr_t *ptr, int val) {
    int *newPtr = (int *) malloc((ptr->len + 1) * sizeof(int));
    for (int i = 0; i < ptr->len; i++)
        newPtr[i] = ptr->c[i];
    newPtr[ptr->len] = val;
    ptr->len++;
    free(ptr->c);
    ptr->c = newPtr;
}

arr_t *array() {
    arr_t *ptr = (arr_t *) malloc(sizeof(arr_t));
    ptr->len = 0;
    ptr->c = NULL;
    return ptr;
}

typedef enum {
    WHITE,
    GREY,
    BLACK
} color;

int procCnt, resCnt;
arr_t *procToRess;
arr_t *resToProcs;
color *visited;
bool cycle = false;

void dfs_proc(int cur);
void dfs_res(int cur);

void dfs_proc(int cur) {
    visited[cur] = GREY;
    for (int i = 0; i < procToRess[cur].len; i++) {
        int rid = procToRess[cur].c[i];
        dfs_res(rid);
        if (cycle)
            return;
    }
    visited[cur] = BLACK;
}

void dfs_res(int cur) {
    for (int i = 0; i < resToProcs[cur].len; i++) {
        int pid = resToProcs[cur].c[i];
        if (visited[pid] == GREY) {
            cycle = true;
            return;
        }
        if (visited[pid] == WHITE) {
            dfs_proc(pid);
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d %d", &procCnt, &resCnt);

    // Map: process -> array of resources
    procToRess = (arr_t *) malloc(procCnt * sizeof(arr_t));
    for (int i = 0; i < procCnt; i++) {
        procToRess[i].len = 0;
        procToRess[i].c = NULL;
    }

    // Map: resource -> array of processes
    resToProcs = (arr_t *) malloc(resCnt * sizeof(arr_t));
    for (int i = 0; i < resCnt; i++) {
        resToProcs[i].len = 0;
        resToProcs[i].c = NULL;
    }

    // Write already allocated resources.
    for (int p = 0; p < procCnt; p++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int id;
            scanf("%d", &id);
            add(resToProcs + id, p);
            add(procToRess + p, id);
        }
    }

    // Write required resources
    for (int p = 0; p < procCnt; p++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int id;
            scanf("%d", &id);
            add(resToProcs + id, p);
            add(procToRess + p, id);
        }
    }

    visited = (color *) malloc(sizeof(color) * procCnt);
    for (int i =0; i < procCnt; i++)
        visited[i] = WHITE;

    for (int i = 0; i < procCnt; i++)
        if (visited[i] == WHITE)
            dfs_proc(i);

    printf("Deadlock is %s present\n", cycle ? "" : "not");
}

