#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;

int main() {
    Perf perf;
    long long result = 0;

    for (string line : input::readLines("input.txt")) {
        
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
