#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;

const int BOX_COUNT = 256;

struct Lens {
    string label;
    int focalLength;
    Lens(string label, int focalLenght) {
        this->label = label;
        this->focalLength = focalLenght;
    };
};

int hashLabel(const string& label) {
    int hash = 0;

    for (char c : label) {
        hash += (int)c;
        hash *= 17;
        hash %= 256;
    }

    return hash;
}

void removeLens(vector<Lens> (&boxes)[BOX_COUNT], const string& label) {
    int hash = hashLabel(label);
    vector<Lens>::iterator it = boxes[hash].begin();

    while (it != boxes[hash].end()) {
        if (it->label == label) {
            boxes[hash].erase(it);
            break;
        }

        it++;
    }
}

void upsertLens(vector<Lens> (&boxes)[BOX_COUNT], const string& label, const int focalLength) {
    bool updated = false;
    int hash = hashLabel(label);

    for (Lens& lens : boxes[hash]) {
        if (lens.label == label) {
            lens.focalLength = focalLength;
            updated = true;
            break;
        }
    }

    if (!updated) {
        boxes[hash].push_back(Lens(label, focalLength));
    }
}

int main() {
    Perf perf;
    int result = 0;
    vector<Lens> boxes[BOX_COUNT];
    string sequence = input::readLines("input.txt").at(0);
    vector<string> steps = input::split(sequence, ","); 

    for (string step : steps) {
        if (step[step.length() - 1] == '-') {
            string label = step.substr(0, step.size() - 1);
            removeLens(boxes, label);
            continue;
        }

        vector<string> parts = input::split(step, "=");
        upsertLens(boxes, parts.at(0), stoi(parts.at(1)));
    }

    for (int box = 0; box < BOX_COUNT; box++) {
        for (int slot = 0; slot < boxes[box].size(); slot++) {
            result += (box + 1) * (slot + 1) * boxes[box][slot].focalLength;
        }
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
