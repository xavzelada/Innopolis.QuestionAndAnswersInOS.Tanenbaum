#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

typedef enum {
    INTEGER,
    FLOAT,
    STRING
} ARG_T;

ARG_T types[] = {INTEGER, FLOAT, STRING};

typedef struct {
    ARG_T type;
    void *ptr
} ARG;

typedef struct {
    int argc;
    ARG *args;
    char *format;
} Req;

#define FORMAT_LEN 64

void server_stub(Req *arg) {
    char *format = arg->format;

    /*
     * Here should be the logic of deconstruction of Req and its passing to printf. However, I did not find any
     * proper way to pass arguments to printf one-by-one.
     *
     * Only if I was able to somehow modify va_list for vsprintf or construct own one..
     */
}

Req *client_stub() {
    Req *res = (Req *) malloc(sizeof(Req));
    char *format = (char *) malloc(FORMAT_LEN * sizeof(char));
    printf("Enter format string: ");
    scanf("%s\n", format);
    int argc;
    printf("Enter number of arguments: ");
    scanf("%d", &argc);
    res->argc = argc;
    res->args = (ARG *) malloc(argc * sizeof(ARG *));
    for (int i = 0; i < argc; i++) {
        printf("Enter type of arguement (0 for int, 1 for float, 2 for string): ");
        int typeN;
        scanf("%d", &typeN);
        ARG_T type = types[typeN];

        if (type == INTEGER) {
            ARG *ap = (res->args) + i;
            ap->type = type;
            int *val = (int*) malloc(sizeof(int));
            printf("Enter integer argument: ");
            scanf("%d", val);
            ap->ptr = val;
        } else if (type == FLOAT) {
            ARG *ap = (res->args) + i;
            ap->type = type;
            float *val = (float*) malloc(sizeof(float));
            printf("Enter float argument: ");
            scanf("%f", val);
            ap->ptr = val;
        } else if (type == STRING) {
            ARG *ap = (res->args) + i;
            ap->type = type;

            char buf[128] = "";
            printf("Enter string argument: ");
            scanf("%s\n", buf);
            int len = strlen(buf);

            char *val = (char *) malloc(sizeof(char) * len + 1);
            strcpy(val, buf);
            ap->ptr = val;
        } else {
            printf("Wrong type number. Repeat.\n");
            i--;
        }
    }
    return res;
}

int main() {
    printf("%d", "3232");
    return 0;
}





