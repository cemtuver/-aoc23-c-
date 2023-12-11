#include <iostream>
#include <vector>

using namespace std;

struct Galaxy { 
    int r;
    int c;

    Galaxy(int r, int c) {
        this->r = r;
        this->c = c;
    };
};

void expandGalaxies(
    vector<string> image,
    int* rowExpansionCounts, 
    int* columnExpansionCounts, 
    int rows, 
    int columns
) {
    for (int r = 0; r < rows; r++) {
        rowExpansionCounts[r] = 0;
    }

    for (int c = 0; c < columns; c++) {
        columnExpansionCounts[c] = 0;
    }

    for (int r = rows - 1; r >= 0; r--) {
        if (image.at(r).find('#') == -1) {
            for (int re = r; re < rows; re++) {
                rowExpansionCounts[re] += 1;
            }
        }
    }

    for (int c = columns - 1; c >= 0; c--) {
        bool isColumnEmpty = true;
        
        for (int r = 0; r < rows; r++) {
            if (image.at(r).at(c) == '#') {
                isColumnEmpty = false;
                break;
            }
        }

        if (isColumnEmpty) {
            for (int ce = c; ce < columns; ce++) {
                columnExpansionCounts[ce] += 1;
            }
        }
    }
}

long long int sumGalaxyDistances(vector<string> image, int expansionSize) {
    long long int result = 0;
    int rows = image.size();
    int columns = image.at(0).length();
    vector<Galaxy> galaxies;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (image.at(r).at(c) == '#') {
                galaxies.push_back(Galaxy(r, c));
            }
        }
    }

    int rowExpansionCounts[rows];
    int columnExpansionCounts[columns];

    expandGalaxies(
        image,
        rowExpansionCounts,
        columnExpansionCounts,
        rows,
        columns
    );

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            Galaxy galaxy1 = galaxies.at(i);
            Galaxy galaxy2 = galaxies.at(j);

            result += abs(galaxy1.r - galaxy2.r) + 
                abs(galaxy1.c - galaxy2.c) +
                abs(rowExpansionCounts[galaxy1.r] - rowExpansionCounts[galaxy2.r]) * expansionSize +
                abs(columnExpansionCounts[galaxy1.c] - columnExpansionCounts[galaxy2.c]) * expansionSize;
        }
    }

    return result;
}
