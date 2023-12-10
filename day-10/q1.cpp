#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Pipe.cpp"

using namespace std;

Point findFirstConnection(
    vector<string>& pipes, 
    Point startPoint, 
    int rows, 
    int columns
);

int findDistance(
    vector<string>& pipes, 
    Point currentPoint, 
    Point previousPoint, 
    int currentDistance,
    int rows,
    int columns
);

int main() {
    Perf perf;
    int result = 0;
    vector<string> pipes = input::readLines("input.txt");
    int rows = pipes.size();
    int columns = pipes.at(0).length();
    Point startPoint = Point(-1, -1);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (pipes.at(r).at(c) == 'S') {
                startPoint.r = r;
                startPoint.c = c;
            }
        }
    }

    result = findDistance(
        pipes, 
        findFirstConnection(pipes, startPoint, rows, columns),
        startPoint, 
        1, 
        rows, 
        columns
    );

    cout << result / 2 << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}

Point findFirstConnection(
    vector<string>& pipes, 
    Point startPoint, 
    int rows, 
    int columns
) {
    for (Point neighbourConnection : neighbourConnections) {
        Point connectionPoint = startPoint + neighbourConnection;

        if (!connectionPoint.isInRange(rows, columns)) {
            continue;
        }

        char pipe = pipes.at(connectionPoint.r).at(connectionPoint.c);
        Connection connection = pipeConnections[pipe];

        if (connectionPoint + connection.diff1 == startPoint || connectionPoint + connection.diff2 == startPoint) {
            return connectionPoint;
        }
    }

    throw invalid_argument("There is no valid first connection!");
}


int findDistance(
    vector<string>& pipes, 
    Point currentPoint, 
    Point previousPoint, 
    int currentDistance,
    int rows,
    int columns
) {
    char pipe = pipes.at(currentPoint.r).at(currentPoint.c);

    if (pipes[currentPoint.r][currentPoint.c] == 'S') {
        return currentDistance;
    }

    Point nextPoint;
    Connection connection = pipeConnections[pipe];

    if (currentPoint + connection.diff1 == previousPoint) {
        nextPoint = currentPoint + connection.diff2;
    } else {
        nextPoint = currentPoint + connection.diff1;
    }

    return findDistance(pipes, nextPoint, currentPoint, currentDistance + 1, rows, columns);
}
