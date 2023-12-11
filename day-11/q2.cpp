#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Galaxy.cpp"

using namespace std;

int main() {
    Perf perf;
    long long int result = 0;
    vector<string> image = input::readLines("input.txt");

    result = sumGalaxyDistances(image, 1000000 - 1);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
