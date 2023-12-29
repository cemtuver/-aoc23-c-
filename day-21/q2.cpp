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

    long long mapCount = 26501365LL / size - 1;
    long long numberOfFullOddMaps = pow(mapCount / 2 * 2 + 1, 2);
    long long numberOfFullEvenMaps = pow((mapCount + 1) / 2 * 2, 2);
    long long oddPoints = countReachablePoints(map, startPoint, size * 2 + 1);
    long long evenPoints = countReachablePoints(map, startPoint, size * 2);
    long long totalFullPoints = numberOfFullOddMaps * oddPoints + numberOfFullEvenMaps * evenPoints;

    long long cornerTopPoints = countReachablePoints(map, Point(size - 1, startPoint.c), size - 1);
    long long cornerRightPoints = countReachablePoints(map, Point(startPoint.r, 0), size - 1);
    long long cornerBottomPoints = countReachablePoints(map, Point(0, startPoint.c), size - 1);
    long long cornerLeftPoints = countReachablePoints(map, Point(startPoint.r, size - 1), size - 1);
    long long totalCornerPoints = cornerTopPoints + cornerRightPoints + cornerBottomPoints + cornerLeftPoints;

    long long edgeTopRightPoints1 = countReachablePoints(map, Point(size - 1, 0), size / 2 - 1);
    long long edgeTopLeftPoints1 = countReachablePoints(map, Point(size - 1, size - 1), size / 2 - 1);
    long long edgeBottomRightPoints1 = countReachablePoints(map, Point(0, 0), size / 2 - 1);
    long long edgeBottomLeftPoints1 = countReachablePoints(map, Point(0, size - 1), size / 2 - 1);
    long long totalEdgePoints1 = (mapCount + 1) * (edgeTopRightPoints1 + edgeTopLeftPoints1 + edgeBottomRightPoints1 + edgeBottomLeftPoints1);

    long long edgeTopRightPoints2 = countReachablePoints(map, Point(size - 1, 0), size * 3 / 2 - 1);
    long long edgeTopLeftPoints2 = countReachablePoints(map, Point(size - 1, size - 1), size * 3 / 2 - 1);
    long long edgeBottomRightPoints2 = countReachablePoints(map, Point(0, 0), size * 3 / 2 - 1);
    long long edgeBottomLeftPoints2 = countReachablePoints(map, Point(0, size - 1), size * 3 / 2 - 1);
    long long totalEdgePoints2 = mapCount * (edgeTopRightPoints2 + edgeTopLeftPoints2 + edgeBottomRightPoints2 + edgeBottomLeftPoints2);

    result = totalFullPoints + totalCornerPoints + totalEdgePoints1 + totalEdgePoints2;

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
