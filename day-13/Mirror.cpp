#include <iostream>
#include <vector>
#include "../lib/Math.hpp"

using namespace std;

int findMirrorIndex(const vector<int>& mirror, int expectedSmudgeCount) {
    for (int i = 1; i < mirror.size(); i++) {
        int left = i - 1;
        int right = i;
        int smudgeCount = 0;

        while (left >= 0 && right < mirror.size()) {
            smudgeCount += math::setBitDiff(mirror[left], mirror[right]);

            left--;
            right++;
        }

        if (smudgeCount == expectedSmudgeCount) {
            return i;
        }
    }

    return 0;
}

int countMirrorIndexes(const vector<string>& lines, int expectedSmudgeCount) {
    int count = 0;
    vector<int> rows;
    vector<int> columns;

    for (string line : lines) {
        if (line.length() == 0) {
            count += findMirrorIndex(rows, expectedSmudgeCount) * 100;
            count += findMirrorIndex(columns, expectedSmudgeCount);

            rows.clear();
            columns.clear();
            continue;
        }

        int row = 0;
        int columnIndex = rows.size();

        if (columns.empty()) {
            for (int i = 0; i < line.length(); i++) {
                columns.push_back(0);
            }
        }

        for (int i = 0; i < line.length(); i++) {
            if (line[i] != '#') {
                continue;
            }

            row = row | (1 << i);
            columns[i] = columns[i] | (1 << columnIndex);
        }

        rows.push_back(row);
    }

    count += findMirrorIndex(rows, expectedSmudgeCount) * 100;
    count += findMirrorIndex(columns, expectedSmudgeCount);

    return count;
}
