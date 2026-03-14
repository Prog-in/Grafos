#include "../include/A1_1.h"

#include <fstream>

void Undirected_Weighted_Graph::store(const unsigned int u, const unsigned int v, const unsigned int weight) const {
    const unsigned int max = u >= v ? u : v;
    const unsigned int min = u >= v ? v : u;
    rowAt(min).at(max) = weight;
}

Undirected_Weighted_Graph::Undirected_Weighted_Graph(const std::string& arquivo) {
    std::ifstream fd(arquivo);
    std::string line;
    std::string w;
    unsigned int nVertex;

    // *vertices n
    std::getline(fd, line) >> w >> nVertex;

    _m = std::vector<std::pair<std::string, std::vector<unsigned int>>>(nVertex);
    for (unsigned int i = 0; i < nVertex; ++i) {
        auto row = std::vector<unsigned int>(nVertex-i, 0);
        _m.emplace_back(std::pair("", row));
    }

    // i i_label
    for (unsigned int i = 0; i < nVertex; ++i) {
        int vertex;
        std::getline(fd, line) >> vertex >> w;
        _m[vertex].first = w;
    }

    unsigned int nEdges = 0;
    int u, v, weight;

    // *edges
    std::getline(fd, line);

    // u v weight
    while (std::getline(fd, line) >> u >> v >> weight) {
        nEdges++;
        store(u, v, weight);
    }
}

unsigned int Undirected_Weighted_Graph::qtdVertices() const {
    return _m.size();
}

unsigned int Undirected_Weighted_Graph::qtdArestas() const {
    unsigned int c = 0;
    for (unsigned int i = 0; i < qtdVertices(); ++i) {
        c += rowAt(i).size();
    }
    return c;
}

unsigned int Undirected_Weighted_Graph::grau(const unsigned int v) const {
    unsigned int d = 0;
    for (const unsigned int edge : rowAt(v)) {
        d += edge != 0;
    }
    return d;
}

// TODO: tipo do rotulo
std::string Undirected_Weighted_Graph::rotulo(const unsigned int v) const {
    return _m[v].first;
}

std::vector<unsigned int> Undirected_Weighted_Graph::vizinhos(const unsigned int v) const {
    const std::vector<unsigned int> row = rowAt(v);
    std::vector<unsigned int> neighbours;
    for (unsigned col = 0; col < row.size(); ++col) {
        if (row[col] != 0) {
            neighbours.push_back(col);
        }
    }
    return neighbours;
}

bool Undirected_Weighted_Graph::haAresta(const unsigned int u, const unsigned int v) const {
    return peso(u, v) != 0;
}

unsigned int Undirected_Weighted_Graph::peso(const unsigned int u, const unsigned int v) const {
    const unsigned int max = u >= v ? u : v;
    const unsigned int min = u >= v ? v : u;
    return rowAt(min)[max];
}
