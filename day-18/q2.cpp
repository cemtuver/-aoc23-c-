#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "DigPlan.cpp"

using namespace std;

int main() {
    Perf perf;
    long long result = 0;
    vector<Point> points;
    Point currentPoint = Point(0, 0);
    points.push_back(currentPoint);

    for (string line : input::readLines("input.txt")) {
        Point nextPoint = currentPoint;
        string hexCode = line.substr(line.length() - 7, 6);
        char direction = hexCode[hexCode.length() - 1];
        long long distance = strtoll(hexCode.substr(0, 5).c_str(), NULL, 16);

        if (direction == '0') nextPoint.c = currentPoint.c + distance;
        else if (direction == '1') nextPoint.r = currentPoint.r + distance;
        else if (direction == '2') nextPoint.c = currentPoint.c - distance;
        else if (direction == '3') nextPoint.r = currentPoint.r - distance;

        currentPoint = nextPoint;
        points.push_back(nextPoint);
    }

    result = calculateInnerArea(points) + calculateEdgeLength(points);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
