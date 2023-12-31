#include <iostream>
#include <vector>
#include <set>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Point.cpp"

using namespace std;

char slopes[] {
    '^',
    '>',
    'v',
    '<'
};

void traverse(
    const vector<string>& map,
    Point currentPoint, 
    int currentSteps, 
    set<Point>& visitedPoints,
    vector<vector<int>>& maxSteps
) {
    if (map[currentPoint.r][currentPoint.c] == '#') return;
    if (visitedPoints.find(currentPoint) != visitedPoints.end()) return;

    int rows = map.size();
    int columns = map.at(0).size();
    char tile = map[currentPoint.r][currentPoint.c];

    visitedPoints.insert(currentPoint);
    maxSteps[currentPoint.r][currentPoint.c] = max(currentSteps, maxSteps[currentPoint.r][currentPoint.c]);

    for (int direction = 0; direction < 4; direction++) {
        if (tile != '.' && tile != slopes[direction]) {
            continue;
        }

        Point nextPoint = currentPoint + velocities[direction];

        if (nextPoint.isInRange(rows, columns)) {
            traverse(map, nextPoint, currentSteps + 1, visitedPoints, maxSteps);
        }
    }

    visitedPoints.erase(currentPoint);
}

int main() {
    Perf perf;
    long long result = 0;
    vector<string> map = input::readLines("input.txt");
    int rows = map.size();
    int columns = map.at(0).size();
    Point startPoint, endPoint;

    for (int c = 0; c < columns; c++) {
        if (map[0][c] == '.') startPoint = Point(0, c);
        if (map[rows - 1][c] == '.') endPoint = Point(rows - 1, c);
    }

    set<Point> visitedPoints;
    vector<vector<int>> maxSteps(rows, vector(columns, 0));

    traverse(map, startPoint, 0, visitedPoints, maxSteps);
    result = maxSteps[endPoint.r][endPoint.c];

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
