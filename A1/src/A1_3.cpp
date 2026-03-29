#include <iostream>
#include <ostream>
#include <algorithm>
#include <deque>

#include "../include/A1_1.h"

// usa o algoritmo de Hierholzer com uma stack para achar o ciclo euleriano
void cicloEuleriano(Undirected_Weighted_Graph& graph)
{
    unsigned int edge_count = graph.qtdArestas();
    if (edge_count == 0) {
        std::cout << "1\n\n";
        return;
    }

    std::vector<std::vector<bool>> marked
        (graph.qtdVertices(), std::vector<bool>(graph.qtdVertices(), false));

    std::deque<unsigned int> path{};
    std::deque<unsigned int> q{};

    unsigned int v = 0;
    while (graph.grau(v + 1) == 0)
        v++;
    q.push_back(v);

    while (q.size() > 0) {
        v = q.back();
        bool found_edge = false;

        if (graph.grau(v + 1) % 2 == 1) {
            std::cout << "0\n";
            return;
        }

        for (const auto &u : graph.vizinhos(v + 1)) {
            if (graph.haAresta(v + 1, u)
                  and not marked[v][u - 1]
                  and not found_edge) {
                q.push_back(u - 1);
                marked[v][u - 1] = true;
                marked[u - 1][v] = true;
                found_edge = true;
                edge_count -= 1;
            }
        }

        if (not found_edge) {
            path.push_back(v);
            q.pop_back();
        }
    }

    if (edge_count != 0) {
        std::cout << "0\n";
        return;
    }

    std::cout << "1\n";
    for (size_t i = 0; i < path.size() - 1; i++) {
        std::cout << path[i] + 1 << ',';
    }
    std::cout << path[0] + 1 << '\n';
}

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "The program must receive 1 argument: the graph file." << std::endl;
        return 1;
    }

    const std::string graph_file = argv[1];

    auto graph = Undirected_Weighted_Graph(graph_file);
    cicloEuleriano(graph);

    return 0;
}
