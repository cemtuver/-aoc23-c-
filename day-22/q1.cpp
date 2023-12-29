#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Brick.cpp"

using namespace std;

int main() {
    Perf perf;
    long long result = 0;
    vector<Brick> bricks = parseAndfallBricks(input::readLines("input.txt"));

    for (int i = 0; i < bricks.size(); i++) {
        bool canDisintegrated = true;

        for (int supportedBrick : bricks.at(i).supportedBricks) {
            if (bricks.at(supportedBrick).supportBricks.size() <= 1) {
                canDisintegrated = false;
                break;
            }
        }

        result += canDisintegrated;
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
