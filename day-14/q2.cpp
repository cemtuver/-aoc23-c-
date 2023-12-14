#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Tilting.cpp"

using namespace std;

void tiltCycle(vector<string>& map, int rows, int columns) {
    tiltNorth(map, rows, columns);
    tiltWest(map, rows, columns);
    tiltSouth(map, rows, columns);
    tiltEast(map, rows, columns);
}

int main() {
    Perf perf;
    int result = 0;
    int cycleCount = 1000000000;
    vector<string> map = input::readLines("input.txt");
    int rows = map.size();
    int columns = map.at(0).length();

    int currentCycle = 1;
    int remainingCycle = 0;
    unordered_map<std::string, int> mapCache;
    mapCache[generateMapKey(map)] = 0;

    while (true) {
        tiltCycle(map, rows, columns);
        string mapKey = generateMapKey(map);

        if (mapCache.find(mapKey) != mapCache.end()) {
            remainingCycle = (cycleCount - mapCache[mapKey]) % (currentCycle - mapCache[mapKey]);
            break;
        }

        mapCache[mapKey] = currentCycle;
        currentCycle++;
    }

    for (int i = 0; i < remainingCycle; i++) {
        tiltCycle(map, rows, columns);
    }

    result = calculateNorthLoad(map, rows, columns);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
