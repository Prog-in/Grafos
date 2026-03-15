#ifndef GRAFOS_A1_1_H
#define GRAFOS_A1_1_H
#include <limits>
#include <string>
#include <utility>
#include <vector>

class Undirected_Weighted_Graph {
    static constexpr float DEFAULT_EDGE_WEIGHT = std::numeric_limits<float>::max();
    // Using optimization: m as upper triangular matrix
    std::vector<std::pair<std::string, std::vector<float>>> _m;
    // degrees of each vertex
    std::vector<unsigned int> _d;
    std::vector<std::vector<unsigned int>> _neighbours;
    unsigned int nEdges;

    void store(unsigned int u, unsigned int v, float weight);

public:
    explicit Undirected_Weighted_Graph(const std::string& arquivo);

    unsigned int qtdVertices() const;
    unsigned int qtdArestas() const;
    unsigned int grau(unsigned int v) const;
    std::string& rotulo(unsigned int v);
    std::vector<unsigned int>& vizinhos(unsigned int v);
    bool haAresta(unsigned int u, unsigned int v) const;
    float peso(unsigned int u, unsigned int v) const;
};

#endif //GRAFOS_A1_1_H