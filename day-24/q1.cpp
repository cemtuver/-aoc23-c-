#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;

struct Point {
    long double x;
    long double y;
    long double z;

    Point(): Point(0, 0, 0) { }

    Point(long double x, long double y, long double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point(const string& pointString) {
        vector<long long> pointParts = input::splitLongLong(pointString, ", ");
        this->x = (long double)pointParts.at(0);
        this->y = (long double)pointParts.at(1);
        this->z = (long double)pointParts.at(2);
    }

    Point operator+(const Point& other) const {
        return Point(this->x + other.x, this->y + other.y, this->z + other.z);
    }
};

struct Hail {
    Point position;
    Point velocity;

    Hail() { }

    Hail(const string& hailString) {
        vector<string> hailParts = input::split(hailString, " @ ");
        this->position = Point(hailParts.at(0));
        this->velocity = Point(hailParts.at(1));
    }
};

bool intersects(const Hail& hail1, const Hail& hail2, long double minXY, long double maxXY) {
    Point p1 = hail1.position;
    Point v1 = hail1.velocity;
    Point p1End = p1 + v1;
    Point p2 = hail2.position;
    Point v2 = hail2.velocity;
    Point p2End = p2 + v2;

    long double u = (p1.y * v2.x + v2.y * p2.x - p2.y * v2.x - v2.y * p1.x) / (v1.x * v2.y - v1.y * v2.x);
    long double v = (p1.x + v1.x * u - p2.x) / v2.x;

    if (u <= 0 || v <= 0) {
        return false;
    }

    long double m1 = (p1End.y - p1.y) / (p1End.x - p1.x);
    long double m2 = (p2End.y - p2.y) / (p2End.x - p2.x);
    long double b1 = p1.y - m1 * p1.x;
    long double b2 = p2.y - m2 * p2.x;
    long double px = (b2 - b1) / (m1 - m2);
    long double py = m1 * px + b1;

    return px >= minXY && px <= maxXY && py >= minXY && py <= maxXY;
}

int main() {
    Perf perf;
    long long result = 0;
    long double minXY = 200000000000000.0l;
    long double maxXY = 400000000000000.0l;
    vector<Hail> hails;

    for (string line : input::readLines("input.txt")) {
        hails.emplace_back(line);
    }

    for (int i = 0; i < hails.size(); i++) {
        for (int j = i + 1; j < hails.size(); j++) {
            if (intersects(hails.at(i), hails.at(j), minXY, maxXY)) {
                result++;
            }
        }
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
