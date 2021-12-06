#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define SEG_LEN 2

int N;
std::vector <std::unordered_map<std::string, int>> wc;
std::vector <std::string> text;

void *worker(void *args) {
    int index = (long) args;
    for (int i = 0; index * SEG_LEN + i < (index + 1) * SEG_LEN; ++i) {
        wc[index + 1][text[index * SEG_LEN + i]]++;
    }
    std::string report;
    report += "Report for thread number: " + std::to_string(index) + "\n";
    for (auto p : wc[index + 1]) {
        report += "Word \"" + p.first + "\" frequency is " + std::to_string(p.second) + "\n";
    }
    std::cout << report;
}

int main() {
    freopen("input.txt", "r", stdin);
    std::cin >> N;
    wc.resize(N + 1);
    text.resize(N * SEG_LEN);
    for (std::string &s : text) {
        std::cin >> s;
    }
    pthread_t threads[N];
    for (int i = 0; i < N; ++i) {
        pthread_create(&threads[i], NULL, worker, (void *) (i));
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 1; i <= N; ++i) {
        for (auto p : wc[i]) {
            wc[0][p.first] += p.second;
        }
    }
    for (auto p : wc[0]) {
        std::cout << "Total frequency of the word \"" << p.first << "\" is " << p.second << "\n";
    }
}
