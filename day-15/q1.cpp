#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;

int main() {
    Perf perf;
    int result = 0;
    string sequence = input::readLines("input.txt").at(0);
    vector<string> steps = input::split(sequence, ","); 

    for (string step : steps) {
        int hash = 0;
        
        for (char c : step) {
            hash += (int)c;
            hash *= 17;
            hash %= 256;
        }

        result += hash;
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
