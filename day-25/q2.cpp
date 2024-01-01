#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;

int main() {
    Perf perf;
    long long result = 0;

    cout << "Happy holidays and a new year!" << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
