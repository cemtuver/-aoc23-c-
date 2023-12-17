#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Crucible.cpp"

using namespace std;

int main() {
    Perf perf;
    int result = 0;
    vector<string> lines = input::readLines("input.txt"); 

    result = findMinimumHeatLoss(lines, 3, 1);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
