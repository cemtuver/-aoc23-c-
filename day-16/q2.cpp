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
    int rows = lines.size();
    int columns = lines.at(0).length();

    for (int c = 0; c < columns; c++) {
        result = max(result, countEnergizedTiles(lines, Beam(Point(-1, c), DOWN)));
    }

    for (int c = 0; c < columns; c++) {
        result = max(result, countEnergizedTiles(lines, Beam(Point(rows, c), UP)));
    }

    for (int r = 0; r < rows; r++) {
        result = max(result, countEnergizedTiles(lines, Beam(Point(r, -1), RIGHT)));
    }

    for (int r = 0; r < rows; r++) {
        result = max(result, countEnergizedTiles(lines, Beam(Point(r, columns), LEFT)));
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
