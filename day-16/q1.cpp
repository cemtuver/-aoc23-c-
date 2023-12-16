#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Beam.cpp"

using namespace std;

int main() {
    Perf perf;
    int result = 0;
    vector<string> lines = input::readLines("input.txt");
    Beam startBeam = Beam(Point(0, -1), RIGHT);
    
    result = countEnergizedTiles(lines, startBeam);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
