#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;
int findNextElement(const vector<int>& numbers);

int main() {
    Perf perf;
    int result = 0;

    for (string line : input::readLines("input.txt")) {
        vector<int> numbers = input::splitInt(line, " ");
        reverse(numbers.begin(), numbers.end());

        result += findNextElement(numbers);
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}

int findNextElement(const vector<int>& numbers) {
    bool isEndSequance = numbers[0] == 0;
    int lastElement = numbers.at(numbers.size() - 1);
    vector<int> reducedNumbers;

    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] != 0) {
            isEndSequance = false;
        }

        reducedNumbers.push_back(numbers.at(i) - numbers.at(i - 1));
    }

    return isEndSequance ? 0 : lastElement + findNextElement(reducedNumbers);
}
