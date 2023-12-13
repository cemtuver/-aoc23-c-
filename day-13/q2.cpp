#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Mirror.cpp"

using namespace std;

int main() {
    Perf perf;
    int result = countMirrorIndexes(input::readLines("input.txt"), 1);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
