#include <iostream>
#include <vector>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Workflow.cpp"

using namespace std;

struct Part {
    char name;
    int count;
    Part(const string& line) {
        vector<string> parts = input::split(line, "=");
        this->name = parts[0][0];
        this->count = stoi(parts[1]);
    };
};

bool ruleMatches(const Rule& rule, const vector<Part>& parts) {
    if (rule.isOperationFree) return true;

    for (Part part : parts) {
        if (rule.partName != part.name) continue;
        if (rule.operation == '<' && rule.value > part.count) return true;
        if (rule.operation == '>' && rule.value < part.count) return true;
    }

    return false;
}

bool isAccepted(unordered_map<string, Workflow>& workflows, vector<Part>& parts) {
    Workflow currentWorkflow = workflows["in"];

    while (true) {
        for (Rule rule : currentWorkflow.rules) {
            if (ruleMatches(rule, parts)) {
                if (rule.targetWorkflow == "A") return true;
                if (rule.targetWorkflow == "R") return false;

                currentWorkflow = workflows[rule.targetWorkflow];
                break;
            }
        }
    }

    return false;
}

int main() {
    Perf perf;
    int result = 0;
    bool parsingWorkflows = true;
    unordered_map<string, Workflow> workflows;

    for (string line : input::readLines("input.txt")) {
        if (line == "") {
            parsingWorkflows = false;
            continue;
        }

        if (parsingWorkflows) {
            Workflow workflow = Workflow(line);
            workflows.insert_or_assign(workflow.name, workflow);
            continue;
        }

        line.erase(0, 1);
        line.erase(line.length() - 1);
        vector<string> partStrings = input::split(line, ",");
        vector<Part> parts;

        for (string partString : partStrings) {
            parts.push_back(Part(partString));
        }

        if (isAccepted(workflows, parts)) {
            for (Part part : parts) {
                result += part.count;
            }
        }
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
