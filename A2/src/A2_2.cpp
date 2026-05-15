#include <iostream>
#include <list>
#include <vector>

#include "../include/A2_Graph.h"

void topologicalOrdering(Directed_Weighted_Graph& g)
{
    /* algoritmo de Kahn de https://en.wikipedia.org/wiki/Topological_sorting */
    std::list<unsigned int> topo;
    std::vector<std::vector<bool>> marked
        (g.qtdVertices(), std::vector<bool>(g.qtdVertices(), false));
    std::vector<int> deg (g.qtdVertices());
    std::list<unsigned int> S;

    for (unsigned int v = 1; v <= g.qtdVertices(); v++) {
        deg[v - 1] = g.grauMenos(v);
        if (g.grauMenos(v) == 0) {
            S.push_back(v);
        }
    }

    for (unsigned int u : S) {
        topo.push_back(u);
        for (unsigned int v : g.vizinhosFora(u)) {
            if (marked[u - 1][v - 1] == false) {
                marked[u - 1][v - 1] = true;
                deg[v - 1]--;
            }
            if (deg[v - 1] == 0)
                S.push_back(v);
        }
    }

    for (auto it = topo.begin(); *it != topo.back(); it++) {
        std::cout << g.rotulo(*it) << " , ";
    }
    std::cout << g.rotulo(topo.back()) << '\n';
}

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "The program must receive one arguments: the graph file" << std::endl;
        return 1;
    }

    const std::string graph_file = argv[1];

    auto graph = Directed_Weighted_Graph(graph_file);
    topologicalOrdering(graph);

    return 0;
}
