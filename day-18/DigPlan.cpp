#include <vector>

struct Point {
    long long r;
    long long c;
    Point(): Point(0, 0) { };
    Point(const Point& other) : Point(other.r, other.c) { }
    Point(long long r, long long c) {
        this->r = r;
        this->c = c;
    }
};

long long calculateEdgeLength(const std::vector<Point> points) {
    long long edgeLength = 0;

    for (int i = 1; i < points.size(); i++) {
        Point currentPoint = points.at(i - 1);
        Point nextPoint = points.at(i);

        edgeLength += llabs(currentPoint.r - nextPoint.r) + llabs(currentPoint.c - nextPoint.c);
    }

    return (edgeLength / 2ll) + 1ll;
}

long long calculateInnerArea(const std::vector<Point> points) {
    long long leftSum = 0;
    long long rightSum = 0;

    for (int i = 0; i < points.size(); ++i) {
        int j = (i + 1) % points.size();
        leftSum += points[i].r * points[j].c;
        rightSum += points[j].r * points[i].c;
    }

    return llabs(leftSum - rightSum) / 2ll;
}
