//
// Created by Junhaum Hayden on 5/14/26.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <iomanip>

#include "../../A2/include/A1_1.h"  // Caminho relativo para Undirected_Weighted_Graph

// Detectar ciclos
struct UnionFind {
    std::vector<int> parent, rank;
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank[px] < rank[py]) parent[px] = py;
        else {
            parent[py] = px;
            if (rank[px] == rank[py]) rank[px]++;
        }
        return true;
    }
};

void kruskal(Undirected_Weighted_Graph& graph, float& totalWeight, std::vector<std::pair<int, int>>& mstEdges) {
    int n = graph.qtdVertices();
    std::vector<std::tuple<float, int, int>> edges;

    // Coletar todas as arestas
    for (int u = 1; u <= n; ++u) {
        for (int v : graph.vizinhos(u)) {
            if (u < v) {  // Evitar duplicatas devido à simetria
                float w = graph.peso(u, v);
                edges.emplace_back(w, u, v);
            }
        }
    }

    // Ordenar arestas por peso
    std::sort(edges.begin(), edges.end());

    UnionFind uf(n);
    totalWeight = 0.0f;
    mstEdges.clear();

    for (auto& [w, u, v] : edges) {
        if (uf.unite(u - 1, v - 1)) {  // u-1 e v-1 para índices 0-based
            totalWeight += w;
            mstEdges.emplace_back(std::min(u, v), std::max(u, v));
        }
    }

    // Ordenar arestas da MST por u, depois v
    std::sort(mstEdges.begin(), mstEdges.end());
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_grafo>" << std::endl;
        return 1;
    }

    std::string graphFile = argv[1];
    Undirected_Weighted_Graph graph(graphFile);

    float totalWeight;
    std::vector<std::pair<int, int>> mstEdges;
    kruskal(graph, totalWeight, mstEdges);

    // Imprimir soma
    std::cout << std::fixed << std::setprecision(1) << totalWeight << std::endl;

    // Imprimir arestas
    for (size_t i = 0; i < mstEdges.size(); ++i) {
        std::cout << mstEdges[i].first << "-" << mstEdges[i].second;
        if (i < mstEdges.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    return 0;
}