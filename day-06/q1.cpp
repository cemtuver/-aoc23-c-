#include <iostream>
#include <vector>
#include <string>
#include "../lib/Input.hpp"

using namespace std;

int main() {
    int result = 1;
    vector<string> lines = input::readLines("input.txt");
    vector<int> times = input::splitInt(lines.at(0).substr(9), " ");
    vector<int> distances = input::splitInt(lines.at(1).substr(9), " ");

    for (int i = 0; i < times.size(); i++) {
        int time = times.at(i);
        int distance = distances.at(i) + 1;

        // distance = (time - pressTime) * pressTime
        // distance = (time * pressTime) - (pressTime * pressTime)
        // (pressTime * pressTime) - (time * pressTime) + distance = 0

        int pressTimeHigh = floor((time + sqrt(time * time - 4 * distance)) / 2);
        int pressTimeLow = ceil((time - sqrt(time * time - 4 * distance)) / 2);

        result *= pressTimeHigh - pressTimeLow + 1;
    }

    cout << result << endl;

    return 0;
}
