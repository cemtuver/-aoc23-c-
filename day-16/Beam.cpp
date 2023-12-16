#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

struct Point {
    int r;
    int c;
    Point(): Point(0, 0) { };
    Point(int r, int c) {
        this->r = r;
        this->c = c;
    };
    Point operator+(Point other) {
        return Point(this->r + other.r, this->c + other.c);
    }
    bool isInRange(int rows, int columns) {
        return this->r >= 0 && this->r < rows &&
            this->c >= 0 && this->c < columns;
    }
};

Point velocities[] = {
    Point(-1, 0),
    Point(0, 1),
    Point(1, 0),
    Point(0, -1),
};

struct Beam {
    Point point;
    Direction direction;
    Beam(Point point, Direction direction) {
        this->point = point;
        this->direction = direction;
    };
};

int countEnergizedTiles(const vector<string>& lines, Beam startBeam) {
    int result = 0;
    int rows = lines.size();
    int columns = lines.at(0).length();
    int map[rows][columns];

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            map[r][c] = lines[r][c];
        }
    }

    queue<Beam> beams;
    int energized[rows][columns];
    beams.push(startBeam);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            energized[r][c] = 0;
        }
    }

    while (!beams.empty()) {
        Beam beam = beams.front();
        beams.pop();
        
        while (true) {
            int energy = 1 << (int)beam.direction;
            Point nextPoint = beam.point + velocities[beam.direction];

            if (!nextPoint.isInRange(rows, columns)) {
                energized[beam.point.r][beam.point.c] |= energy;
                break;
            }

            if ((energized[nextPoint.r][nextPoint.c] & energy) > 0) {
                break;
            }
 
            if (map[nextPoint.r][nextPoint.c] == '/') {
                if (beam.direction == UP) beam.direction = RIGHT;
                else if (beam.direction == RIGHT) beam.direction = UP;
                else if (beam.direction == DOWN) beam.direction = LEFT;
                else if (beam.direction == LEFT) beam.direction = DOWN;
            } else if (map[nextPoint.r][nextPoint.c] == '\\') {
                if (beam.direction == UP) beam.direction = LEFT;
                else if (beam.direction == RIGHT) beam.direction = DOWN;
                else if (beam.direction == DOWN) beam.direction = RIGHT;
                else if (beam.direction == LEFT) beam.direction = UP;
            } else if (map[nextPoint.r][nextPoint.c] == '|') {
                if (beam.direction == LEFT || beam.direction == RIGHT) {
                    beams.push(Beam(nextPoint, UP));
                    beam.direction = DOWN;
                }
            } else if (map[nextPoint.r][nextPoint.c] == '-') {
                if (beam.direction == UP || beam.direction == DOWN) {
                    beams.push(Beam(nextPoint, LEFT));
                    beam.direction = RIGHT;
                }
            }

            beam.point = nextPoint;
            energized[nextPoint.r][nextPoint.c] |= energy;
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            result += (int)(energized[r][c] > 0);
        }
    }

    return result;
}
