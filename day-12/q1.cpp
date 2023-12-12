#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "SpringRecord.cpp"

using namespace std;

int main() {
    Perf perf;
    long long int result = 0;

    for (string line : input::readLines("input.txt")) {
        unordered_map<string, long long> cache;
        SpringRecord springRecord = parseSpringRecord(line, 1);

        result += findNumberOfPossibleSolutions(
            cache, 
            springRecord.record, 
            springRecord.contiguousGroups, 
            0, 
            0
        );
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
