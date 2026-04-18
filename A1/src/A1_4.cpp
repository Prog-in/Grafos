#include <iostream>
#include <ostream>
#include <algorithm>
#include <deque>
#include <list>

#include "../include/A1_1.h"

std::vector<std::list<unsigned int>> make_paths(Undirected_Weighted_Graph &G, std::vector<unsigned int> &A)
{
    std::vector<std::list<unsigned int>> ret(G.qtdVertices(), std::list<unsigned int>());

    for (size_t i = 1; i <= G.qtdVertices(); i++) {
        unsigned int k = i;
        do {
            ret[i - 1].push_front(k);
            k = A[k - 1];
        } while (k != 0 or k == i);
    }

    return ret;
}

void bellmanFord(Undirected_Weighted_Graph& graph, unsigned int source)
{
    std::vector<float> D(graph.qtdVertices(), std::numeric_limits<float>::max());
    std::vector<unsigned int> A(graph.qtdVertices(), 0);

    D[source - 1] = 0;
    for (size_t i = 0; i < graph.qtdVertices(); i++) {
        for (size_t j = 1; j <= graph.qtdVertices(); j++) {
            for (auto const &k : graph.vizinhos(j)) {
                if (D[k - 1] > D[j - 1] + graph.peso(j, k)) {
                    D[k - 1] = D[j - 1] + graph.peso(j, k);
                    A[k - 1] = j;
                }
            }
        }
    }

    auto paths = make_paths(graph, A);

    for (size_t i = 1; i <= graph.qtdVertices(); i++) {
        auto it = paths[i - 1].begin();
        std::cout << i << ": ";
        while (*it != paths[i - 1].back()) {
            std::cout << *it << ',';
            it++;
        }
        std::cout << paths[i - 1].back() << "; ";
        std::cout << "d=" << D[i - 1] << '\n';
    }
}

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "The program must receive 2 argument: the graph file and the source vertex." << std::endl;
        return 1;
    }

    const std::string graph_file = argv[1];
    const unsigned int v = atoi(argv[2]);

    auto graph = Undirected_Weighted_Graph(graph_file);
    bellmanFord(graph, v);

    return 0;
}
