#include <iostream>
#include <ostream>
#include <algorithm>

#include "../include/A1_1.h"

void bfs(Undirected_Weighted_Graph& graph, const std::vector<unsigned int>& levelNodes, std::vector<bool> marked,
        const unsigned int level) {
    if (levelNodes.empty()) {
        return;
    }
    auto nextLevel = std::vector<unsigned int>();
    for (const unsigned int v : levelNodes) {
        std::vector<unsigned int>& neighbours = graph.vizinhos(v);
        // marking logic
        for (unsigned int neighbour : neighbours) {
            if (!marked[neighbour-1]) {
                nextLevel.push_back(neighbour);
                marked[neighbour-1] = true;
            }
        }
    }
    if (!nextLevel.empty()) {
        // printing levels
        std::cout << level << ": ";
        for (unsigned int i = 0; i < nextLevel.size(); i++) {
            const unsigned int neighbour = nextLevel[i];
            std::cout << neighbour;
            if (i < nextLevel.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << '\n';
    }
    bfs(graph, nextLevel, marked, level + 1);
}

void bfs(Undirected_Weighted_Graph& graph, const unsigned int vIndex) {
    std::cout << "0: " << vIndex << '\n';
    const auto initialLevel = std::vector(1, vIndex);
    auto marked = std::vector(graph.qtdVertices(), false);
    marked[vIndex-1] = true;
    bfs(graph, initialLevel, marked, 1);
}

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "The program must receive 2 arguments: the graph file and the index of the vertex." << std::endl;
        return 1;
    }

    const std::string graph_file = argv[1];
    const unsigned int vIndex = atoi(argv[2]);

    auto graph = Undirected_Weighted_Graph(graph_file);
    bfs(graph, vIndex);

    return 0;
}
