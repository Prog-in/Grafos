#include "../include/A2_Graph.h"

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

void dfs(Directed_Weighted_Graph& graph, const unsigned int u, std::vector<bool>& visited, std::stack<unsigned int>& s) {
    visited[u - 1] = true;
    for (const unsigned int v : graph.vizinhosFora(u)) {
        if (!visited[v - 1]) {
            dfs(graph, v, visited, s);
        }
    }
    s.push(u);
}

void adaptedDfs(Directed_Weighted_Graph& graph, const unsigned int u, std::vector<bool>& visited, std::vector<unsigned int>& component) {
    visited[u - 1] = true;
    component.push_back(u);
    for (const unsigned int v : graph.vizinhosDentro(u)) {
        if (!visited[v - 1]) {
            adaptedDfs(graph, v, visited, component);
        }
    }
}

void stronglyConnectedComponents(Directed_Weighted_Graph& graph) {
    const unsigned int n = graph.qtdVertices();
    std::stack<unsigned int> s;
    std::vector<bool> visited(n, false);

    for (unsigned int i = 1; i <= n; i++) {
        if (!visited[i - 1]) {
            dfs(graph, i, visited, s);
        }
    }

    std::fill(visited.begin(), visited.end(), false);

    while (!s.empty()) {
        const unsigned int u = s.top();
        s.pop();

        if (!visited[u - 1]) {
            std::vector<unsigned int> component;
            adaptedDfs(graph, u, visited, component);

            std::sort(component.begin(), component.end());

            for (size_t i = 0; i < component.size(); i++) {
                std::cout << component[i] << (i == component.size() - 1 ? "" : ",");
            }
            std::cout << '\n';
        }
    }
}

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "The program must receive one arguments: the graph file" << std::endl;
        return 1;
    }

    const std::string graph_file = argv[1];

    auto graph = Directed_Weighted_Graph(graph_file);
    stronglyConnectedComponents(graph);

    return 0;
}