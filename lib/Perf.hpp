#include <chrono>

#pragma once

class Perf {
    private:
        std::chrono::steady_clock::time_point startTime;
    public:
        Perf();
        long long measure();
};
