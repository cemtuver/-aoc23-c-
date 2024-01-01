#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include "../lib/Input.hpp"
#include "../lib/Perf.hpp"
#include "../lib/Math.hpp"

using namespace std;

struct Edge {
    string vertex1;
    string vertex2;

    Edge(string vertex1, string vertex2) {
        this->vertex1 = vertex1;
        this->vertex2 = vertex2;
    }
};

struct Graph {
    set<string> vertices;
    vector<Edge> edges;
};

struct Subset {
    string parent;
    int rank;

    Subset() { }

    Subset(string parent, int rank) {
        this->parent = parent;
        this->rank = rank;
    }
};

string findParent(unordered_map<string, Subset>& subsets, string vertex) {
    if (subsets[vertex].parent != vertex) {
        subsets[vertex].parent = findParent(subsets, subsets[vertex].parent);
    }

    return subsets[vertex].parent;
}

void unionVertices(unordered_map<string, Subset>& subsets, string vertex1, string vertex2) {
    string vertexRoot1 = findParent(subsets, vertex1);
    string vertexRoot2 = findParent(subsets, vertex2);

    if (subsets[vertexRoot1].rank < subsets[vertexRoot2].rank) {
        subsets[vertexRoot1].parent = vertexRoot2;
    } else if (subsets[vertexRoot1].rank > subsets[vertexRoot2].rank) {
        subsets[vertexRoot2].parent = vertexRoot1;
    } else {
        subsets[vertexRoot2].parent = vertexRoot1;
        subsets[vertexRoot1].rank++;
    }
}

unordered_map<string, Subset> findKargerMinCutSubsets(Graph& graph) {
    int numberOfVertices = graph.vertices.size();
    int numberOfEdges = graph.edges.size();
    unordered_map<string, Subset> subsets;

    for (string vertex : graph.vertices) {
       subsets.insert_or_assign(vertex, Subset(vertex, 0));
    }

    while (numberOfVertices > 2) {
        Edge edgeToRemove = graph.edges.at(rand() % numberOfEdges);
        string subset1Parent = findParent(subsets, edgeToRemove.vertex1);
        string subset2Parent = findParent(subsets, edgeToRemove.vertex2);

        if (subset1Parent == subset2Parent) {
            continue;
        }

        numberOfVertices--;
        unionVertices(subsets, subset1Parent, subset2Parent);
    }

    return subsets;
}

int getNumberOfCuts(Graph& graph, unordered_map<string, Subset>& subsets) {
    int numberOfCuts = 0;

    for (Edge edge : graph.edges) {
        string subset1Parent = findParent(subsets, edge.vertex1);
        string subset2Parent = findParent(subsets, edge.vertex2);

        if (subset1Parent != subset2Parent) {
            numberOfCuts++;
        }
    }

    return numberOfCuts;
}

unordered_map<string, int> getSubsetSizes(unordered_map<string, Subset>& subsets) {
    unordered_map<string, int> subsetSizes;

    for (pair<string, Subset> subsetPair : subsets) {
        string parent = subsetPair.second.parent;

        if (subsetSizes.find(parent) == subsetSizes.end()) {
            subsetSizes.insert_or_assign(parent, 1);
        } else {
            subsetSizes.insert_or_assign(parent, subsetSizes[parent] + 1);
        }
    }

    return subsetSizes;
}

int main() {
    Perf perf;
    long long result = 0;
    Graph graph;

    for (string line : input::readLines("input.txt")) {
        vector<string> vertexParts = input::split(line, ": ");
        vector<string> neighbours = input::split(vertexParts.at(1), " ");
        string vertexName = vertexParts.at(0);
        
        for (string neighbour : neighbours) {
            graph.edges.push_back(Edge(vertexName, neighbour));
            graph.vertices.insert(neighbour);    
        }

        graph.vertices.insert(vertexName);
    }

    while (true) {
        unordered_map<string, Subset> subsets = findKargerMinCutSubsets(graph);
        int numberOfCuts = getNumberOfCuts(graph, subsets);

        if (numberOfCuts != 3) {
            continue;
        }

        unordered_map<string, int> subsetSizes = getSubsetSizes(subsets);
        result = accumulate(
            subsetSizes.begin(), 
            subsetSizes.end(), 
            1, 
            [](int acc, pair<string, int> subsetSize) {
                return acc * subsetSize.second;
            }
        );

        break;
    }

    cout << result << endl;
    cout << perf.measure() << " ms" << endl;

    return 0;
}
