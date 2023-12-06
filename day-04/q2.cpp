#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"

using namespace std;
const int MAX_NUMBER = 100, MAX_CARD = 250;

int main() {
    Perf perf;
    int result = 0;
    int copyIndex = 0;
    int copies[MAX_CARD];

    for (int i = 0; i < MAX_CARD; i++) {
        copies[i] = 1;
    }

    for (string line : input::readLines("input.txt")) {
        line.erase(0, line.find(':') + 2);
        int matchingNumbersCount = 0;
        bool winningNumbersLookup[MAX_NUMBER] = { false };
        vector<string> numberParts = input::split(line, " | ");
        vector<int> winningNumbers = input::splitInt(numberParts.at(0), " ");
        vector<int> yourNumbers = input::splitInt(numberParts.at(1), " ");

        for (int winningNumber : winningNumbers) {
            winningNumbersLookup[winningNumber] = true;
        }

        for (int yourNumber : yourNumbers) {
            if (winningNumbersLookup[yourNumber]) {
                matchingNumbersCount++;
            }
        }

        for (int i = 1; i <= matchingNumbersCount; i++) {
            copies[copyIndex + i] += copies[copyIndex];
        }

        result += copies[copyIndex];
        copyIndex++;
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
