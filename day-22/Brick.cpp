#include <iostream>
#include <vector>
#include <set>
#include "../lib/Input.hpp"

using namespace std;

struct Point {
    int x;
    int y;
    int z;
    
    Point() : Point(0, 0, 0) { }

    Point(const string& pointString) {
        vector<int> parts = input::splitInt(pointString, ",");

        this->x =parts.at(0);
        this->y =parts.at(1);
        this->z =parts.at(2);
    }

    Point(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator==(Point other) {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    Point operator+(Point other) {
        return Point(this->x + other.x, this->y + other.y, this->z + other.z);
    }
};

struct Brick {
    Point start;
    Point end;
    set<int> supportBricks = set<int>();
    set<int> supportedBricks = set<int>();

    Brick(const string& brickString) {
        vector<string> parts = input::split(brickString, "~");

        this->start = Point(parts.at(0));
        this->end = Point(parts.at(1));
    }

    Brick(Point start, Point end) {
        this->start = start;
        this->end = end;
    }

    bool intersectsOnXY(const Brick& other) {
        return max(this->start.x, other.start.x) <= min(this->end.x, other.end.x) &&
            max(this->start.y, other.start.y) <= min(this->end.y, other.end.y);
    }
};

void sortBricksByStartZ(vector<Brick>& bricks) {
    sort(bricks.begin(), bricks.end(), [](const Brick& brick1, const Brick& brick2) { 
        return brick1.start.z < brick2.start.z;
    });
}

void fallBricks(vector<Brick>& bricks) {
    for (int i = 0; i < bricks.size(); i++) {
        int maxZ = 1;

        for (int j = 0; j < i; j++) {
            if (bricks.at(i).intersectsOnXY(bricks.at(j))) {
                maxZ = max(maxZ, bricks.at(j).end.z + 1);
            }
        }

        bricks.at(i).end.z -= bricks.at(i).start.z - maxZ;
        bricks.at(i).start.z = maxZ;
    }
}

vector<Brick> parseAndfallBricks(const vector<string>& input) {
    vector<Brick> bricks;

    for (string line : input) {
        bricks.push_back(Brick(line));
    }

    sortBricksByStartZ(bricks);
    fallBricks(bricks);
    sortBricksByStartZ(bricks);

    for (int i = 0; i < bricks.size(); i++) {
        Brick* supportedBrick = &bricks.at(i);

        for (int j = 0; j < i; j++) {
            Brick* supporterBrick = &bricks.at(j);

            if (supportedBrick->intersectsOnXY(*supporterBrick) && supportedBrick->start.z == supporterBrick->end.z + 1) {
                supportedBrick->supportBricks.insert(j);
                supporterBrick->supportedBricks.insert(i);
            }
        }
    }    

    return bricks;
}
