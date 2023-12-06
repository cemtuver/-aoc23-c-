#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include "../lib/Perf.hpp"

using namespace std;

vector<string> words = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
int getDigit(string& line, int i);

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
            int digit = getDigit(line, i);

            if (digit == -1) {
                continue;
            }

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

int getDigit(string& line, int i) {
    if (isdigit(line[i])) {
        return line[i] - '0';
    }

    for (int j = 0; j < words.size(); j++) {
        bool matches = true;
        string& word = words[j]; 

        if (word.length() - 1 > i) {
            continue;
        }

        for (int k = 0; k < word.length(); k++) {
            if (word[word.length() - 1 - k] != line[i - k]) {
                matches = false;
                break;
            }
        }
        
        if (matches) {
            return j;
        }
    }

    return -1;
}
