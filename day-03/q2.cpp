#include <iostream>
#include <string>
#include <cctype>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"

using namespace std;
struct number { int number; int row; int columnStart; int columnEnd; };
struct gear { int partNumberCount; int gearRatio; };

int main() {
    Perf perf;
    int result = 0;
    vector<number> numbers;
    vector<string> lines = input::readLines("input.txt");
    int rows = lines.size();
    int columns = lines.at(0).length();
    char schematic[rows][columns];
    gear* gears[rows][columns];

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            gears[r][c] = NULL;
        }
    }

    for (int r = 0; r < rows; r++) {
        int columnStart = -1;
        int columnEnd = -1;
        string numberString = "";
        string line = lines.at(r);

        for (int c = 0; c < columns; c++) {
            char character = line.at(c);

            if (isdigit(character)) {
                if (columnStart == -1) {
                    columnStart = c;
                }

                columnEnd = c;
                numberString += character;
                schematic[r][c] = '.';
            } else {
                if (columnStart != -1) {
                    number newNumber;
                    newNumber.row = r;
                    newNumber.columnStart = columnStart;
                    newNumber.columnEnd = columnEnd;
                    newNumber.number = stoi(numberString);

                    numbers.push_back(newNumber);
                    columnStart = -1;
                    columnEnd = -1;
                    numberString = "";
                }

                schematic[r][c] = character;

                if (character == '*') {
                    gear* newGear = new gear;
                    newGear->gearRatio = 1;
                    newGear->partNumberCount = 0;

                    gears[r][c] = newGear;
                }
            }
        }

        if (columnStart != -1) {
            number newNumber;
            newNumber.row = r;
            newNumber.columnStart = columnStart;
            newNumber.columnEnd = columnEnd;
            newNumber.number = stoi(numberString);

            numbers.push_back(newNumber);
        }
    }

    for (number n : numbers) {
        for (int r = n.row - 1; r <= n.row + 1; r++) {
            if (r < 0 || r >= rows) {
                continue;
            }

            for (int c = n.columnStart - 1; c <= n.columnEnd + 1; c++) {
                if (c < 0 || c >= columns) {
                    continue;
                }

                if (schematic[r][c] == '*') {
                    if (gears[r][c] != NULL) {
                        gears[r][c]->partNumberCount++;
                        gears[r][c]->gearRatio *= n.number;
                    }
                }
            }
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (gears[r][c] == NULL) {
                continue;
            }

            if (gears[r][c]->partNumberCount == 2) {
                result += gears[r][c]->gearRatio;
            }

            delete gears[r][c];
        }
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
