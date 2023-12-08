#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"

using namespace std;
struct Node { string name; string left; string rigth; };
Node parseNode(string& input);

int main() {
    Perf perf;
    int result = 0;
    vector<string> lines = input::readLines("input.txt");
    string instructions = lines.at(0);
    unordered_map<string, Node> nodeMap;

    lines.erase(lines.begin(), lines.begin() + 2);

    for (string line : lines) {
        Node node = parseNode(line);
        nodeMap[node.name] = node;
    }

    Node currentNode = nodeMap["AAA"];

    while (currentNode.name != "ZZZ") {
        char direction = instructions.at(result % instructions.size());

        currentNode = nodeMap[direction == 'L' ? currentNode.left : currentNode.rigth];
        result++;
    }

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
