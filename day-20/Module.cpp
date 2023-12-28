#include <iostream>
#include <vector>
#include "../lib/Input.hpp"

using namespace std;

enum Pulse {
    LOW,
    HIGH
};

class Module {
private:
    string name;
    vector<string> destinations;
public:
    Module(const string& name, const string& destionationsString) {
        this->name = name;
        this->destinations = input::split(destionationsString, ", ");
    }

    const string getName() {
        return this->name;
    }

    const vector<string> getDestinations() {
        return this->destinations;
    }

    virtual void connectSource(const string& source) { }

    virtual const optional<Pulse> processPulse(const string& source, const Pulse pulse) = 0;
};

class BroadcastModule : public Module {
public:
    BroadcastModule(const string& name, const string& destionationsString) : Module(name, destionationsString) { }

    const optional<Pulse> processPulse(const string& source, const Pulse pulse) override {
        return pulse;
    }
};

class FlipFlopModule : public Module {
private:
    bool isOn = false;
public:
    FlipFlopModule(const string& name, const string& destionationsString) : Module(name, destionationsString) { }

    const optional<Pulse> processPulse(const string& source, const Pulse pulse) override {
        if (pulse == HIGH) return {};

        this->isOn = !this->isOn;
        return this->isOn ? HIGH : LOW;
    }
};

class ConjunctionModule : public Module {
private:
    unordered_map<string, Pulse> memory;
public:    
    ConjunctionModule(const string& name, const string& destionationsString) : Module(name, destionationsString) { }

    void connectSource(const string& source) override {
        this->memory[source] = LOW;
    }

    const optional<Pulse> processPulse(const string& source, const Pulse pulse) override {
        this->memory[source] = pulse;

        for (pair<string, Pulse> sourcePulse : this->memory) {
            if (sourcePulse.second == LOW) {
                return HIGH;
            }
        }

        return LOW;
    }
};

struct Signal {
    string source;
    string destination;
    Pulse pulse;
    Signal(const string& source, const string& destination, const Pulse pulse) {
        this->source = source;
        this->destination = destination;
        this->pulse = pulse;
    }
};

Module* parseModule(const string& line) {
    Module* module;
    vector<string> parts = input::split(line, " -> ");
    string name = parts.at(0);
    string destinationsString = parts.at(1);

    if (name.at(0) == '%') module = new FlipFlopModule(name.erase(0, 1), destinationsString);
    else if (name.at(0) == '&') module = new ConjunctionModule(name.erase(0, 1), destinationsString);
    else module = new BroadcastModule(name, destinationsString);

    return module;
}

void connectModules(const unordered_map<string, Module*>& modules) {
    for (pair<string, Module*> moduleName : modules) {
        Module* module = moduleName.second;

        for (string destinationName : module->getDestinations()) {
            if (modules.find(destinationName) == modules.end()) {
                continue;
            }

            Module* destinationModule = modules.at(destinationName);
            destinationModule->connectSource(module->getName());
        }
    }
}

unordered_map<string, Module*> parseAndConnectModules(const vector<string>& lines) {
    unordered_map<string, Module*> modules;

    for (string line : lines) {
        Module* module = parseModule(line);
        modules.insert_or_assign(module->getName(), module);
    }

    connectModules(modules);

    return modules;
}
