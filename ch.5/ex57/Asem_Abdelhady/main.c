
#include <limits.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define true 1
#define false 0
//returning the command
char * getCommand(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

int main() {
    // time will keep current time
    // pTimer will keep index of last added timer
    // doneTimer will keep index of last alarmed timer
    int time, pTimer = 0, doneTimers = 0;
    // timer array will consist of all provided timers
    // (each element is time instance, when timer should alarm)
    int timers[100];

    // initially all timers contains minimum integer in order not to provide
    // signal accidentally
    for (int i = 0; i < 100; ++i) {
        timers[i] = INT_MIN;
    }

    printf("To finish the program write \"end\"");
    printf("Enter the command Lines for timers: \n");

    // we read input tape until there are some commands in file
    while (true) {

        char*commandLine = getCommand();
        if(strcmp (commandLine, "ctrl + C") == 0) break;
        char type = commandLine[0];

        // before process provided data we assume that time wasn't changed
        int timeChanged = false;
        switch (type) {
            // if we get s - command, we change current time into provided one
            case 's':
               time = (int)commandLine[1];
                // if we get t - command, we should increment current time
                // and notify our flag timeChanged, that time indeed was changed
            case 't':
                time++;
                timeChanged = true;
                break;
                // if we get e - command, we should add new timer to timers array
                // and increment pointer to next free slot of timers in timers array
                // then we will sort all timers in increasing order
                // to keep latest timer on the rightmost position
            case 'e':
                timers[pTimer++] = (int)commandLine[1];
                // here we just sort array
                for (int i = doneTimers; i < pTimer - 1; i++) {
                    for (int j = 0; j < pTimer - i - 1; j++) {
                        if (timers[j] > timers[j + 1]) {
                            int tmp = timers[j];
                            timers[j] = timers[j + 1];
                            timers[j + 1] = tmp;
                        }
                    }
                }
                break;
                // if we get p - command, we should print proper small
                // report about system status
            case 'p':
                // if all timers already alarmed, there are no timers to work in
                // future by this clock-tick
                if (doneTimers == pTimer) {
                    printf("current time: %d\n"
                           "No timers, new one will be #%d\n\n",
                           time, doneTimers + 1);
                } else {
                    printf("current time: %d\n"
                           "Until timer#%d clock ticks left: %d\n\n",
                           time, doneTimers + 1,
                           timers[doneTimers] - time);
                }
                break;
        }

        if (timeChanged) {
            for (int i = 0; i < pTimer; ++i) {
                if (timers[i] == INT_MIN) {
                    continue;
                }
                // if we changed time, timers set for earlier time will never work again
                if (timers[i] < time && timers[i] != INT_MIN) {
                    doneTimers++;
                    timers[i] = INT_MIN;
                }
                if (timers[i] == time) {
                    printf("Timer #%d went to zero!\n\n", i + 1);
                    doneTimers++;
                    timers[i] = INT_MIN;
                }
            }
        }

    }

    return 0;
}
