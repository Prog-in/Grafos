#include <iostream>
#include <ostream>
#include <algorithm>

#include "../include/A1_1.h"

void bfs(const Undirected_Weighted_Graph& graph, const std::vector<unsigned int>& levelNodes, std::vector<bool> marked,
        const unsigned int level) {
    if (levelNodes.empty()) {
        return;
    }
    auto nextLevel = std::vector<unsigned int>();
    for (const unsigned int v : levelNodes) {
        const std::vector<unsigned int> neighbours = graph.vizinhos(v);
        // marking logic
        for (unsigned int neighbour : neighbours) {
            if (!marked[neighbour]) {
                nextLevel.push_back(neighbour);
                marked[neighbour] = true;
            }
        }
    }
    if (!nextLevel.empty()) {
        // printing levels
        std::cout << level << ": ";
        for (unsigned int i = 0; i < nextLevel.size(); i++) {
            const unsigned int neighbour = nextLevel[i];
            std::cout << neighbour+1;
            if (i < nextLevel.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << '\n';
    }
    bfs(graph, nextLevel, marked, level + 1);
}

void bfs(const Undirected_Weighted_Graph& graph, unsigned int vIndex) {
    std::cout << "0: " << vIndex << '\n';
    vIndex--;
    const auto q = std::vector(1, vIndex);
    auto marked = std::vector(graph.qtdVertices(), false);
    marked[vIndex] = true;
    bfs(graph, q, marked, 1);
}

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "The program must receive 2 arguments: the graph file and the index of the vertex." << std::endl;
        return 1;
    }

    const std::string graph_file = argv[1];
    const unsigned int vIndex = atoi(argv[2]);

    const auto graph = Undirected_Weighted_Graph(graph_file);
    bfs(graph, vIndex);

    return 0;
}
