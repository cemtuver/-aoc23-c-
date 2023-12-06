#include <iostream>
#include <fstream>
#include <cctype>
#include "../lib/Perf.hpp"

using namespace std;

int main() {
    Perf perf;
    int result = 0;
    string line;
    ifstream input("input.txt");
    
    if (!input) {
        return -1;
    }

    while (getline(input, line)) {
        int first = -1, last = -1;

        for (int i = 0; i < line.size(); i++) {
            if (!isdigit(line[i])) {
                continue;
            }
            
            int digit = line[i] - '0';

            if (first == -1) {
                first = digit;
            } else {
                last = digit;
            }

            if (last == -1) {
                last = first;
            }
        }

        result += first * 10 + last;
    }

    input.close();
    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
