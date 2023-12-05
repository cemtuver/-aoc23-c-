#include <iostream>
#include <vector>
#include "../lib/Input.hpp"

using namespace std;
struct element { long start; long end; };

int main() {
    long result = LONG_MAX;
    vector<string> lines = input::readLines("input.txt");
    vector<long> seeds = input::splitLong(lines.at(0).substr(7), " ");
    vector<element> sourceElements;
    vector<element> destinationElements;

    for (vector<long>::iterator it = seeds.begin(); it != seeds.end(); it += 2) {
        element newElement;
        newElement.start = *it;
        newElement.end = *it + *(it + 1) - 1;

        destinationElements.push_back(newElement);
    }

    lines.erase(lines.begin(), lines.begin() + 2);

    for (string line : lines) {
        if (line.empty()) {
            vector<element>::iterator it = sourceElements.begin();

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
        vector<element>::iterator it = sourceElements.begin();
        long mappingStart = mappings.at(1);
        long mappingEnd = mappings.at(1) + mappings.at(2) - 1;
        long shift = mappings.at(0) - mappings.at(1);

        while (!sourceElements.empty() && it != sourceElements.end()) {
            element source = *it;

            if (source.start > mappingEnd || source.end < mappingStart) {
                it++;
            } else {
                element destionation;
                destionation.start = max(source.start, mappingStart) + shift;
                destionation.end = min(source.end, mappingEnd) + shift;

                if (source.start < mappingStart) {
                    element newSource;
                    newSource.start = source.start;
                    newSource.end = mappingStart - 1;

                    sourceElements.push_back(newSource);
                }

                if (source.end > mappingEnd) {
                    element newSource;
                    newSource.start = mappingEnd + 1;
                    newSource.end = source.end;

                    sourceElements.push_back(newSource);
                }

                destinationElements.push_back(destionation);
                it = sourceElements.erase(it);
            }        
        }
    }

    for (element source : sourceElements) {
        result = min(result, source.start);
    }

    for (element destination : destinationElements) {
        result = min(result, destination.start);
    }

    cout << result << endl;

    return 0;
}
