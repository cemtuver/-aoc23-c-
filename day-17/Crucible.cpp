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
    }
    Point operator+(const Point& other) const {
        return Point(this->r + other.r, this->c + other.c);
    }
    bool operator==(const Point& other) const {
        return this->r == other.r && this->c == other.c;
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

struct State {
    Point point;
    Direction direction;
    int moveTowardsDirection;
    State() : State(Point(), RIGHT, 0) { }
    State(Point point, Direction direction, int moveTowardsDirection) {
        this->point = point;
        this->direction = direction;
        this->moveTowardsDirection = moveTowardsDirection;
    }
    bool operator==(const State& other) const {
        return this->point == other.point && 
            this->direction == other.direction &&
            this->moveTowardsDirection == other.moveTowardsDirection;
    }
};

struct Crucible {
    State state;
    int heatLoss;
    Crucible(State state, int heatLoss) {
        this->state = state;
        this->heatLoss = heatLoss;
    }
};

template <>
struct std::hash<State> {
    size_t operator()(const State& state) const {
        size_t result = 17;

        result = 31 * result + state.point.r;
        result = 31 * result + state.point.c;
        result = 31 * result + state.direction;
        result = 31 * result + state.moveTowardsDirection;

        return result;
    }
};

State getNextLeftState(const Crucible& crucible) {
    Direction nextDirection;

    if (crucible.state.direction == UP) nextDirection = LEFT;
    else if (crucible.state.direction == RIGHT) nextDirection = UP;
    else if (crucible.state.direction == DOWN) nextDirection = RIGHT;
    else if (crucible.state.direction == LEFT) nextDirection = DOWN;

    return State(crucible.state.point + velocities[nextDirection], nextDirection, 1);
};

State getNextRightState(const Crucible& crucible) {
    Direction nextDirection;

    if (crucible.state.direction == UP) nextDirection = RIGHT;
    else if (crucible.state.direction == RIGHT) nextDirection = DOWN;
    else if (crucible.state.direction == DOWN) nextDirection = LEFT;
    else if (crucible.state.direction == LEFT) nextDirection = UP;

    return State(crucible.state.point + velocities[nextDirection], nextDirection, 1);
};

int findMinimumHeatLoss(
    const vector<string>& lines, 
    int maxStraightMove,
    int minimumStraightMoveBeforeTurn
) {
    int minimumHeatLoss = INT_MAX;
    int rows = lines.size();
    int columns = lines.at(0).length();
    vector<vector<int>> heatLosses;

    for (int r = 0; r < rows; r++) {
        heatLosses.push_back(vector<int>());
        for (int c = 0; c < columns; c++) {
            heatLosses[r].push_back((int)lines[r][c] - '0');
        }
    }

    Point destination = Point(rows - 1, columns - 1);
    unordered_map<State, int> costs;
    queue<Crucible> crucibles;
    crucibles.push(Crucible(State(Point(0, -1), RIGHT, 0), -1 * heatLosses[0][0]));
    crucibles.push(Crucible(State(Point(-1, 0), DOWN, 0), -1 * heatLosses[0][0]));

    while (!crucibles.empty()) {
        Crucible crucible = crucibles.front();
        crucibles.pop();

        if (crucible.state.point == destination) {
            continue;
        }

        if (crucible.state.moveTowardsDirection < maxStraightMove) {
            Point nextPoint = crucible.state.point + velocities[crucible.state.direction];

            if (nextPoint.isInRange(rows, columns)) {
                State nextState = State(nextPoint, crucible.state.direction, crucible.state.moveTowardsDirection + 1);
                int nextHeatLoss = crucible.heatLoss + heatLosses[nextPoint.r][nextPoint.c];

                if (costs.find(nextState) == costs.end() || costs[nextState] > nextHeatLoss) {
                    costs[nextState] = nextHeatLoss;
                    crucibles.push(Crucible(nextState, nextHeatLoss));
                }
            }
        }

        if (crucible.state.moveTowardsDirection >= minimumStraightMoveBeforeTurn) {
            State nextLeftState = getNextLeftState(crucible);
            Point nextLeftPoint = nextLeftState.point;

            if (nextLeftPoint.isInRange(rows, columns)) {
                int nextLeftHeatLoss = crucible.heatLoss + heatLosses[nextLeftPoint.r][nextLeftPoint.c];

                if (costs.find(nextLeftState) == costs.end() || costs[nextLeftState] > nextLeftHeatLoss) {
                    costs[nextLeftState] = nextLeftHeatLoss;
                    crucibles.push(Crucible(nextLeftState, nextLeftHeatLoss));
                }
            }

            State nextRightState = getNextRightState(crucible);
            Point nextRightPoint = nextRightState.point;

            if (nextRightPoint.isInRange(rows, columns)) {
                int nextRightHeatLoss = crucible.heatLoss + heatLosses[nextRightPoint.r][nextRightPoint.c];

                if (costs.find(nextRightState) == costs.end() || costs[nextRightState] > nextRightHeatLoss) {
                    costs[nextRightState] = nextRightHeatLoss;
                    crucibles.push(Crucible(nextRightState, nextRightHeatLoss));
                }
            }
        }       
    }

    for (auto it = costs.begin(); it != costs.end(); it++) {
        if (it->first.point == destination && it->first.moveTowardsDirection >= minimumStraightMoveBeforeTurn) {
            minimumHeatLoss = min(minimumHeatLoss, it->second);
        }
    }

    return minimumHeatLoss;
}
