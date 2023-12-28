#include <iostream>
#include "../lib/Input.hpp"

using namespace std;

struct Rule {
    char partName;
    char operation;
    int value;
    string targetWorkflow;
    bool isOperationFree;
    Rule(const string& line) {
        if (line.find(':') == -1) {
            this->targetWorkflow = line;
            this->isOperationFree = true;
            return;
        }

        vector<string> parts = input::split(line, ":");
        this->partName = parts[0][0];
        this->operation = parts[0][1];
        this->value = stoi(parts[0].substr(2));
        this->targetWorkflow = parts[1];
        this->isOperationFree = false;
    };
};

struct Workflow {
    string name;
    vector<Rule> rules;
    Workflow() { }
    Workflow(const string& line) {
        vector<string> parts = input::split(line, "{");
        this->name = parts[0];
        this->rules = vector<Rule>();
        string workflowRulesString = parts[1];
        workflowRulesString.erase(workflowRulesString.length() - 1);
        vector<string> workflowRules = input::split(workflowRulesString, ",");

        for (string workFlowRule : workflowRules) {
            this->rules.push_back(Rule(workFlowRule));
        }
    }
};