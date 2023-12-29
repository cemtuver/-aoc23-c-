#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Point.cpp"

using namespace std;

int main() {
    Perf perf;
    long long result = 0;
    vector<string> map = input::readLines("input.txt");
    int size = map.size();
    Point startPoint;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (map[r][c] == 'S') {
                startPoint = Point(r, c);
            }
        }
    }
    
    result = countReachablePoints(map, startPoint, 64);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
