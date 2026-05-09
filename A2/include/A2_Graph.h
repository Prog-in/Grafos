#ifndef GRAFOS_A2_GRAPH_H
#define GRAFOS_A2_GRAPH_H

#include <limits>
#include <string>
#include <utility>
#include <vector>

class Directed_Weighted_Graph {
    static constexpr float DEFAULT_EDGE_WEIGHT = std::numeric_limits<float>::max();
    std::vector<std::pair<std::string, std::vector<float>>> _m;
    // degrees of each vertex
    std::vector<unsigned int> _dp;
    std::vector<unsigned int> _dm;
    std::vector<std::vector<unsigned int>> _inNeighbours;
    std::vector<std::vector<unsigned int>> _outNeighbours;
    unsigned int nEdges;

    void store(unsigned int u, unsigned int v, float weight);

public:
    explicit Directed_Weighted_Graph(const std::string& arquivo);

    unsigned int qtdVertices() const;
    unsigned int qtdArestas() const;
    unsigned int grauMais(unsigned int v) const;
    unsigned int grauMenos(unsigned int v) const;
    std::string& rotulo(unsigned int v);
    std::vector<unsigned int>& vizinhosDentro(unsigned int v);
    std::vector<unsigned int>& vizinhosFora(unsigned int v);
    bool haAresta(unsigned int u, unsigned int v) const;
    float peso(unsigned int u, unsigned int v) const;
};

#endif
