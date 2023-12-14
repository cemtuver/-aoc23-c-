#include <iostream>
#include <vector>

using namespace std;

string generateMapKey(const vector<string>& map) {
    string mapKey = "";

    for (string line : map) {
        mapKey += line;
    }

    return mapKey;
}

void tiltNorth(vector<string>& map, int rows, int columns) {
    for (int i = 1; i < rows; i++) {
        for (int r = i; r > 0; r--) {
            for (int c = 0; c < columns; c++) {
                if (map[r][c] == 'O' && map[r - 1][c] == '.') {
                    map[r][c] = '.';
                    map[r - 1][c] = 'O';
                }
            }
        }
    }
}

void tiltWest(vector<string>& map, int rows, int columns) {
    for (int i = 1; i < columns; i++) {
        for (int c = i; c > 0; c--) {
            for (int r = 0; r < rows; r++) {
                if (map[r][c] == 'O' && map[r][c - 1] == '.') {
                    map[r][c] = '.';
                    map[r][c - 1] = 'O';
                }
            }
        }
    }
}

void tiltSouth(vector<string>& map, int rows, int columns) {
    for (int i = rows - 2; i >= 0; i--) {
        for (int r = i; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                if (map[r][c] == 'O' && map[r + 1][c] == '.') {
                    map[r][c] = '.';
                    map[r + 1][c] = 'O';
                }
            }
        }
    }
}

void tiltEast(vector<string>& map, int rows, int columns) {
    for (int i = columns - 2; i >= 0; i--) {
        for (int c = i; c < columns; c++) {
            for (int r = 0; r < rows; r++) {
                if (map[r][c] == 'O' && map[r][c + 1] == '.') {
                    map[r][c] = '.';
                    map[r][c + 1] = 'O';
                }
            }
        }
    }
}

int calculateNorthLoad(const vector<string>& map, int rows, int columns) {
    int northLoad = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (map[i][j] == 'O') {
                northLoad += abs(i - (int)map.size());
            }
        }
    }

    return northLoad;
}
