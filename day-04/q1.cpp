#include <iostream>
#include <vector>
#include "../lib/Input.hpp"

using namespace std;
const int MAX_NUMBER = 100;

int main() {
    int result = 0;

    for (string line : input::readLines("input.txt")) {
        line.erase(0, line.find(':') + 2);
        int points = 0;
        bool winningNumbersLookup[MAX_NUMBER] = { false };
        vector<string> numberParts = input::split(line, " | ");
        vector<int> winningNumbers = input::splitInt(numberParts.at(0), " ");
        vector<int> yourNumbers = input::splitInt(numberParts.at(1), " ");

        for (int winningNumber : winningNumbers) {
            winningNumbersLookup[winningNumber] = true;
        }

        for (int yourNumber : yourNumbers) {
            if (winningNumbersLookup[yourNumber]) {
                if (points == 0) {
                    points = 1;
                } else {
                    points *= 2;
                }
            }
        }

        result += points;
    }

    cout << result << endl;

    return 0;
}
