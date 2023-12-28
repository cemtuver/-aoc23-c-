#include <iostream>
#include <vector>
#include <numeric>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"
#include "Workflow.cpp"

using namespace std;

struct Range {
    int low;
    int high;
    Range() : Range(0, 0) { }
    Range(int low, int high) {
        this->low = low;
        this->high = high;
    }
    int count() {
        return this->high - this->low + 1;
    }
};

struct Part {
    char name;
    Range range;
    Part(char name, Range range) {
        this->name = name;
        this->range = range;
    };
};

unordered_map<char, Part> intersectMatchingParts(
    const Rule& rule, 
    const unordered_map<char, Part>& parts
) {
    unordered_map<char, Part> matchingParts = parts;

    if (rule.operation == '>') {
        matchingParts.at(rule.partName).range.low = rule.value + 1;
    } else {
        matchingParts.at(rule.partName).range.high = rule.value - 1;
    }

    return matchingParts;
}

unordered_map<char, Part> intersectNotMatchingParts(
    const Rule& rule, 
    const unordered_map<char, Part>& parts
) {
    unordered_map<char, Part> notMatchingParts = parts;

    if (rule.operation == '>') {
        notMatchingParts.at(rule.partName).range.high = rule.value;
    } else {
        notMatchingParts.at(rule.partName).range.low = rule.value;
    }

    return notMatchingParts;
}

long long sumAcceptedCombinations(
    const unordered_map<string, Workflow>& workflows,
    const string& currentWorkflowName,
    int currentRuleIndex,
    const unordered_map<char, Part>& parts
) {
    if (currentWorkflowName == "R") {
        return 0;
    }

    if (currentWorkflowName == "A") {
        return accumulate(
            parts.begin(), 
            parts.end(), 
            1ll, 
            [](long long acc, pair<const char, Part> part) {
                return acc * part.second.range.count();
            }
        );
    }

    Workflow currentWorkflow = workflows.at(currentWorkflowName); 
    Rule currentRule = currentWorkflow.rules.at(currentRuleIndex);

    if (currentRule.isOperationFree) {
        return sumAcceptedCombinations(workflows, currentRule.targetWorkflow, 0, parts);
    }

    return sumAcceptedCombinations(workflows, currentRule.targetWorkflow, 0, intersectMatchingParts(currentRule, parts)) 
        + sumAcceptedCombinations(workflows, currentWorkflowName, currentRuleIndex + 1, intersectNotMatchingParts(currentRule, parts));
}

int main() {
    Perf perf;
    long long result = 0;
    unordered_map<string, Workflow> workflows;
    unordered_map<char, Part> parts;

    parts.insert_or_assign('x', Part('x', Range(1, 4000)));
    parts.insert_or_assign('m', Part('x', Range(1, 4000)));
    parts.insert_or_assign('a', Part('x', Range(1, 4000)));
    parts.insert_or_assign('s', Part('x', Range(1, 4000)));

    for (string line : input::readLines("input.txt")) {
        if (line == "") {
            break;
        }

        Workflow workflow = Workflow(line);
        workflows.insert_or_assign(workflow.name, workflow);
    }

    result = sumAcceptedCombinations(workflows, "in", 0, parts);

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
