#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int r;
    int c;
    Point(): Point(0, 0) { }

    Point(int r, int c) {
        this->r = r;
        this->c = c;
    }

    Point operator+(Point other) {
        return Point(this->r + other.r, this->c + other.c);
    }

    bool isInRange(int size) {
        return this->r >= 0 && this->r < size &&
            this->c >= 0 && this->c < size;
    }
};

Point velocities[] = {
    Point(-1, 0),
    Point(0, 1),
    Point(1, 0),
    Point(0, -1),
};

long long countReachablePoints(const vector<string>& map, Point start, int totalSteps) {
    long long reachablePoints = 0;
    int size = map.size();
    bool seen[size][size];
    bool reached[size][size];

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            seen[r][c] = false;
            reached[r][c] = false;
        }
    }

    queue<pair<Point, int>> points;
    points.emplace(start, totalSteps);

    while (!points.empty()) {
        pair<Point, int> pointPair = points.front();
        Point point = pointPair.first;
        int steps = pointPair.second;
        points.pop();

        if (steps % 2 == 0 && reached[point.r][point.c] == false) {
            reached[point.r][point.c] = true;
            reachablePoints++;
        }

        if (steps == 0) {
            continue;
        }

        for (Point velocity : velocities) {
            Point nextPoint = point + velocity;

            if (!nextPoint.isInRange(size) || seen[nextPoint.r][nextPoint.c] || map[nextPoint.r][nextPoint.c] == '#') {
                continue;
            }

            seen[nextPoint.r][nextPoint.c] = true;
            points.emplace(nextPoint, steps - 1);
        }
    }

    return reachablePoints;
}
