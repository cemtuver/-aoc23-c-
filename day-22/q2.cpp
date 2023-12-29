#include <iostream>
#include <vector>
#include <queue>
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
        queue<int> fallingQueue;
        set<int> fellBricks;
        fellBricks.insert(i);

        for (int supportedBrick : bricks.at(i).supportedBricks) {
            if (bricks.at(supportedBrick).supportBricks.size() == 1) {
                fallingQueue.push(supportedBrick);
                fellBricks.insert(supportedBrick);
            }
        }

        while (!fallingQueue.empty()) {
            int fallingBrick = fallingQueue.front();
            fallingQueue.pop();

            for (int supportedBrickIndex : bricks.at(fallingBrick).supportedBricks) {
                Brick* supportedBrick = &bricks.at(supportedBrickIndex);

                bool allSupportersFell = includes(
                    fellBricks.begin(),
                    fellBricks.end(),
                    supportedBrick->supportBricks.begin(),
                    supportedBrick->supportBricks.end()
                );

                if (fellBricks.find(supportedBrickIndex) == fellBricks.end() && allSupportersFell) {
                    fallingQueue.push(supportedBrickIndex);
                    fellBricks.insert(supportedBrickIndex);
                }
            }
        }

        result += fellBricks.size() - 1;
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
