#include <iostream>
#include <vector>
#include <string>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"

using namespace std;

int main() {
    Perf perf;
    long result;
    vector<string> lines = input::readLines("input.txt");
    string timeString = lines.at(0).substr(9);
    string distanceString = lines.at(1).substr(9);

    input::remove(timeString, ' ');
    input::remove(distanceString, ' ');

    long time = stol(timeString);
    long distance = stol(distanceString) + 1;

    // distance = (time - pressTime) * pressTime
    // distance = (time * pressTime) - (pressTime * pressTime)
    // (pressTime * pressTime) - (time * pressTime) + distance = 0

    long pressTimeHigh = floor((time + sqrt(time * time - 4 * distance)) / 2);
    long pressTimeLow = ceil((time - sqrt(time * time - 4 * distance)) / 2);

    result = pressTimeHigh - pressTimeLow + 1;
    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
