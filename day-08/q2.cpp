#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;
struct Node { string name; string left; string rigth; };
struct Path { Node currentNode; long cycleCount; };
Node parseNode(string& input);
long long int lcmCycleCount(const vector<Path>& paths, int index);

int main() {
    Perf perf;
    long long result = 0;
    vector<string> lines = input::readLines("input.txt");
    string instructions = lines.at(0);
    unordered_map<string, Node> nodeMap;
    vector<Path> paths;

    lines.erase(lines.begin(), lines.begin() + 2);

    for (string line : lines) {
        Node node = parseNode(line);
        nodeMap[node.name] = node;

        if (node.name.at(2) == 'A') {
            Path path;
            path.currentNode = node;
            path.cycleCount = 0;
            paths.push_back(path);
        }
    }

    int cycleCount = 0;
    int completedCycleCount = 0;

    while (completedCycleCount < paths.size()) {
        char direction = instructions.at(cycleCount % instructions.size());

        for (Path& path : paths) {
            path.currentNode = nodeMap[direction == 'L' ? path.currentNode.left : path.currentNode.rigth];

            if (path.currentNode.name.at(2) == 'Z' && path.cycleCount == 0) {
                path.cycleCount = cycleCount + 1;
                completedCycleCount++;
            }
        }

        cycleCount++;
    }

    result = lcmCycleCount(paths, 0);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}

Node parseNode(string& input) {
    input::remove(input, '(');
    input::remove(input, ')');
    vector<string> parts = input::split(input, " = ");
    vector<string> neighbours = input::split(parts.at(1), ", ");

    Node node;
    node.name = parts.at(0);
    node.left = neighbours.at(0);
    node.rigth = neighbours.at(1);

    return node;
}

long long lcmCycleCount(const vector<Path>& paths, int index) {
    if (index == paths.size() - 1) {
        return paths.at(paths.size() - 1).cycleCount;
    }

    return math::lcm(paths.at(index).cycleCount, lcmCycleCount(paths, index + 1));
}

