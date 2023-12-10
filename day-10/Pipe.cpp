#include <vector>

struct Point { 
    int r;
    int c;

    Point(): Point(-1, -1) {};

    Point(int r, int c) {
        this->r = r;
        this->c = c;
    };

    bool operator==(Point other) {
        return this->r == other.r && this->c == other.c;
    }

    Point operator+(Point other) {
        return Point(this->r + other.r, this->c + other.c);
    }

    bool isInRange(int rows, int columns) {
        return this->r >= 0 && this->r < rows && this->c >= 0 && this->c < columns;
    }
};

struct Connection {
    Point diff1;
    Point diff2;

    Connection(): Connection(Point(-1, -1), Point(-1, -1)) {};
    
    Connection(Point diff1, Point diff2) {
        this->diff1 = diff1;
        this->diff2 = diff2;
    };
};

std::vector<Point> neighbourConnections = { 
    Point(-1, 0), 
    Point(0, 1), 
    Point(1, 0), 
    Point(0, -1) 
};

std::unordered_map<char, Connection> pipeConnections = { 
    {'|', Connection(Point(-1, 0), Point(1, 0))},
    {'-', Connection(Point(0, -1), Point(0, 1))},
    {'L', Connection(Point(-1, 0), Point(0, 1))},
    {'J', Connection(Point(-1, 0), Point(0, -1))},
    {'7', Connection(Point(0, -1), Point(1, 0))},
    {'F', Connection(Point(0, 1), Point(1, 0))},
};