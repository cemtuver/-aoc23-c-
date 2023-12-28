#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Module.cpp"

using namespace std;

bool allHigh(const unordered_map<string, int>& highButtonPressCounts) {
    for (pair<string, int> highButtonPressCountPair : highButtonPressCounts) {
        if (highButtonPressCountPair.second == -1) {
            return false;
        }
    }

    return true;
}

void updateHighButtonPressCounts(unordered_map<string, int>& highButtonPressCounts, const string& moduleName, const int buttonPressCount) {
    if (highButtonPressCounts.find(moduleName) != highButtonPressCounts.end() && highButtonPressCounts.at(moduleName) == -1) {
        highButtonPressCounts.insert_or_assign(moduleName, buttonPressCount);   
    }
}

int main() {
    Perf perf;
    long long result = 0;
    int buttonPressCount = 0;
    unordered_map<string, Module*> modules = parseAndConnectModules(input::readLines("input.txt"));
    unordered_map<string, int> highButtonPressCounts;

    highButtonPressCounts["fz"] = -1;
    highButtonPressCounts["xf"] = -1;
    highButtonPressCounts["mp"] = -1;
    highButtonPressCounts["hn"] = -1;

    while (true) {
        if (allHigh(highButtonPressCounts)) {
            break;
        }

        buttonPressCount++;
        queue<Signal> signalQueue;
        signalQueue.emplace("button", "broadcaster", LOW);

        while (!signalQueue.empty()) {
            Signal signal = signalQueue.front();
            signalQueue.pop();

            if (modules.find(signal.destination) == modules.end()) {
                continue;
            }

            Module* module = modules.at(signal.destination);
            optional<Pulse> pulse = module->processPulse(signal.source, signal.pulse);

            if (pulse.has_value()) {
                if (pulse == HIGH) {
                    updateHighButtonPressCounts(highButtonPressCounts, module->getName(), buttonPressCount);
                }

                for (string destination : module->getDestinations()) {
                    signalQueue.emplace(module->getName(), destination, pulse.value());
                }
            }
        }
    }

    result = accumulate(
        highButtonPressCounts.begin(), 
        highButtonPressCounts.end(), 
        1ll, 
        [](long long acc, pair<string, int> highButtonPressCountPair) {
            return math::lcm(acc, highButtonPressCountPair.second);
        }
    );

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
