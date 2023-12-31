#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Point.cpp"

using namespace std;

set<Point> findIntersections(const vector<string>& map, Point startPoint, Point endPoint) {
    int rows = map.size();
    int columns = map.at(0).size();
    set<Point> intersections;

    intersections.insert(startPoint);
    intersections.insert(endPoint);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (map[r][c] == '#') {
                continue;
            }

            Point current = Point(r, c);
            int numberOfNeighbours = 0;

            for (Point velocity : velocities) {
                Point neighbour = current + velocity;

                if (neighbour.isInRange(rows, columns) && map[neighbour.r][neighbour.c] != '#') {
                    numberOfNeighbours++;
                }
            }

            if (numberOfNeighbours >= 3) {
                intersections.insert(current);
            }
        }
    }

    return intersections;
}

unordered_map<Point, unordered_map<Point, int>> findDistances(
    const vector<string>& map, 
    Point startPoint, 
    Point endPoint
) {
    int rows = map.size();
    int columns = map.at(0).size();
    set<Point> intersections = findIntersections(map, startPoint, endPoint);
    unordered_map<Point, unordered_map<Point, int>> distances;

    for (Point intersection : intersections) {
        set<Point> seen;
        queue<pair<Point, int>> queue;
        seen.insert(intersection);
        queue.push(pair(intersection, 0));

        while (!queue.empty()) {
            pair<Point, int> pointDistancePair = queue.front();
            Point point = pointDistancePair.first;
            int distance = pointDistancePair.second;
            queue.pop();

            if (distance != 0 && intersections.find(point) != intersections.end()) {
                distances[intersection][point] = distance;
                continue;
            }

            for (Point velocity : velocities) {
                Point neighbour = point + velocity;

                if (point.isInRange(rows, columns) && map[neighbour.r][neighbour.c] != '#' && seen.find(neighbour) == seen.end()) {
                    seen.insert(neighbour);
                    queue.emplace(neighbour, distance + 1);
                }
            }
        }
    }

    return distances;
}

int findLongestPath(
    unordered_map<Point, unordered_map<Point, int>>& distances, 
    Point currentPoint, 
    Point endPoint,
    set<Point>& seen
) {
    if (currentPoint == endPoint) {
        return 0;
    }

    int distance = INT_MIN;
    seen.insert(currentPoint);

    for (pair<Point, int> neighbourPair : distances[currentPoint]) {
        Point neighbour = neighbourPair.first;
        int neighbourDistance = neighbourPair.second;

        if (seen.find(neighbour) != seen.end()) {
            continue;
        }

        distance = max(distance, findLongestPath(distances, neighbour, endPoint, seen) + neighbourDistance);
    }

    seen.erase(currentPoint);

    return distance;
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

    set<Point> seen;
    unordered_map<Point, unordered_map<Point, int>> distances = findDistances(map, startPoint, endPoint);
    result = findLongestPath(distances, startPoint, endPoint, seen);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
