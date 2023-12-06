#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"

using namespace std;

int main() {
    Perf perf;
    long result = LONG_MAX;
    vector<string> lines = input::readLines("input.txt");
    vector<long> sourceElements;
    vector<long> destinationElements = input::splitLong(lines.at(0).substr(7), " ");

    lines.erase(lines.begin(), lines.begin() + 2);

    for (string line : lines) {
        if (line.empty()) {
            vector<long>::iterator it = sourceElements.begin();

            while (it != sourceElements.end()) {
                destinationElements.push_back(*it);
                it = sourceElements.erase(it);
            }

            continue;
        }

        int titleDelimiterIndex = line.find("-to-");

        if (titleDelimiterIndex > -1) {
            sourceElements.swap(destinationElements);

            continue;
        }

        vector<long> mappings = input::splitLong(line, " ");
        vector<long>::iterator it = sourceElements.begin();

        while (!sourceElements.empty() && it != sourceElements.end()) {
            if (*it >= mappings.at(1) && *it <= mappings.at(1) + mappings.at(2) - 1) {
                long shift = mappings.at(0) - mappings.at(1);

                destinationElements.push_back(*it + shift);
                it = sourceElements.erase(it);
            } else {
                it++;
            }
        }
    }

    for (long source : sourceElements) {
        result = min(result, source);
    }

    for (long destination : destinationElements) {
        result = min(result, destination);
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
