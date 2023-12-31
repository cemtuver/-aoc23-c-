#include <iostream>

struct Point {
    int r;
    int c;
    Point(): Point(0, 0) { }

    Point(int r, int c) {
        this->r = r;
        this->c = c;
    }

    bool operator==(const Point& other) const {
        return this->r == other.r && this->c == other.c;
    }

    Point operator+(const Point& other) const {
        return Point(this->r + other.r, this->c + other.c);
    }

    Point operator-(const Point& other) const {
        return Point(this->r - other.r, this->c - other.c);
    }

    bool operator<(const Point& other) const {
        if (this->r < other.r) return true;
        if (this->r == other.r && this->c < other.c) return true;

        return false;
    }

    bool isInRange(int rows, int columns) {
        return this->r >= 0 && this->r < rows &&
            this->c >= 0 && this->c < columns;
    }
};

template <>
struct std::hash<Point> {
    size_t operator()(const Point& point) const {
        size_t result = 17;

        result = 31 * result + point.r;
        result = 31 * result + point.c;

        return result;
    }
};

Point velocities[] = {
    Point(-1, 0),
    Point(0, 1),
    Point(1, 0),
    Point(0, -1),
};
