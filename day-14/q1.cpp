#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Tilting.cpp"

using namespace std;

int main() {
    Perf perf;
    int result = 0;
    vector<string> map = input::readLines("input.txt");
    int rows = map.size();
    int columns = map.at(0).length();

    tiltNorth(map, rows, columns);
    result = calculateNorthLoad(map, rows, columns);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
