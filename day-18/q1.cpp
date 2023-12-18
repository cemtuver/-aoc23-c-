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
        vector<string> parts = input::split(line, " ");
        string direction = parts.at(0);
        long long distance = stoll(parts.at(1));

        if (direction == "U") nextPoint.r = currentPoint.r - distance;
        else if (direction == "R") nextPoint.c = currentPoint.c + distance;
        else if (direction == "D") nextPoint.r = currentPoint.r + distance;
        else if (direction == "L") nextPoint.c = currentPoint.c - distance;

        currentPoint = nextPoint;
        points.push_back(nextPoint);
    }

    result = calculateInnerArea(points) + calculateEdgeLength(points);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
