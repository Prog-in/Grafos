#ifndef GRAFOS_A1_1_H
#define GRAFOS_A1_1_H
#include <string>
#include <utility>
#include <vector>

class Undirected_Weighted_Graph {
    // Using optimization: m as upper triangular matrix
    std::vector<std::pair<std::string, std::vector<unsigned int>>> _m;

    void store(unsigned int u, unsigned int v, unsigned int weight) const;

    std::vector<unsigned int> rowAt(const unsigned int i) const {
        return _m.at(i).second;
    }

public:
    explicit Undirected_Weighted_Graph(const std::string& arquivo);

    unsigned int qtdVertices() const;
    unsigned int qtdArestas() const;
    unsigned int grau(unsigned int v) const;
    // TODO: tipo do rotulo
    std::string rotulo(unsigned int v) const;
    std::vector<unsigned int> vizinhos(unsigned int v) const;
    bool haAresta(unsigned int u, unsigned int v) const;
    unsigned int peso(unsigned int u, unsigned int v) const;
};

#endif //GRAFOS_A1_1_H