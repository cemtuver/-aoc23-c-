#include <iostream>
#include <vector>
#include <queue>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Module.cpp"

using namespace std;

int main() {
    Perf perf;
    int result = 0;
    int lowPulseCount = 0;
    int highPulseCount = 0;
    unordered_map<string, Module*> modules = parseAndConnectModules(input::readLines("input.txt"));

    for (int i = 0; i < 1000; i++) {
        queue<Signal> signalQueue;
        signalQueue.emplace("button", "broadcaster", LOW);

        while (!signalQueue.empty()) {
            Signal signal = signalQueue.front();
            signalQueue.pop();
            lowPulseCount += signal.pulse == LOW;
            highPulseCount += signal.pulse == HIGH;

            if (modules.find(signal.destination) == modules.end()) {
                continue;
            }

            Module* module = modules.at(signal.destination);
            optional<Pulse> pulse = module->processPulse(signal.source, signal.pulse);

            if (pulse.has_value()) {
                for (string destination : module->getDestinations()) {
                    signalQueue.emplace(module->getName(), destination, pulse.value());
                }
            }
        }
    }

    result = lowPulseCount * highPulseCount;

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
