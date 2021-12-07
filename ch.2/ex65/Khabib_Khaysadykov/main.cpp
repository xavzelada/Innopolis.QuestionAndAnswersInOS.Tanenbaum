#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdint.h>

#define LENGTH 2

using namespace std;

vector <string> text;
int N;
vector <unordered_map<string, int>> wc;

void *worker(void *args) {
    int index = (long) args;
    for (int i = 0; index * LENGTH + i < (index + 1) * LENGTH; ++i) wc[index + 1][text[index * LENGTH + i]]++;
    string report;
    report += "Report from thread : " + to_string(index) + "\n";
    for (auto p : wc[index + 1]) report += "Word \"" + p.first + "\" frequency is " + to_string(p.second) + "\n";
    cout << report;
    return NULL;
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> N;
    wc.resize(N + 1);
    text.resize(N * LENGTH);
    for (string &s : text) cin >> s;
    pthread_t threads[N];

    for (int i = 0; i < N; ++i) pthread_create(&threads[i], NULL, worker, (void *)(uintptr_t)(i));
    for (int i = 0; i < N; ++i) pthread_join(threads[i], NULL);
    for (int i = 1; i <= N; ++i) {
        for (auto p : wc[i]) wc[0][p.first] += p.second;
    }
    for (auto p : wc[0]) 
        cout << "The word [" << p.first << "] has total frequency - " << p.second << "\n";
}




