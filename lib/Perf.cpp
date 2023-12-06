#include <vector>
#include <string>
#include <fstream>
#include "Perf.hpp"

Perf::Perf() {
    this->startTime = std::chrono::high_resolution_clock::now();
}

long long Perf::measure() {
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - this->startTime);
 
    return duration.count();
}