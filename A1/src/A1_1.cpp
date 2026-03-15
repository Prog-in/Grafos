#include "../include/A1_1.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Undirected_Weighted_Graph::store(const unsigned int u, const unsigned int v, const float weight) {
    const unsigned int max = u >= v ? u : v;
    const unsigned int min = u >= v ? v : u;
    // max - min: offset of the row "min" of the upper triangular matrix
     _m.at(min).second[max-min] = weight;
}

Undirected_Weighted_Graph::Undirected_Weighted_Graph(const std::string& arquivo) {
    std::ifstream fd(arquivo);
    std::string line;
    std::string w;
    std::stringstream ss;
    unsigned int nVertices;

    // *vertices n
    std::getline(fd, line);
    ss.str(line);
    ss >> w >> nVertices;

    _m = std::vector<std::pair<std::string, std::vector<float>>>(nVertices);
    for (unsigned int i = 0; i < nVertices; ++i) {
        auto row = std::vector(nVertices-i, DEFAULT_EDGE_WEIGHT);
        _m[i] = std::pair("", row);
    }
    _d = std::vector<unsigned int>(nVertices, 0);
    _neighbours = std::vector<std::vector<unsigned int>>(nVertices);

    // (i+1) (i+1)_label
    for (unsigned int i = 0; i < nVertices; ++i) {
        unsigned int vertex;
        std::getline(fd, line);
        ss.clear();
        ss.str(line);
        ss >> vertex >> w;
        --vertex;
        _m[vertex].first = w;
        _neighbours[vertex] = std::vector<unsigned int>();
    }

    nEdges = 0;
    int u, v;
    float weight;

    // *edges
    std::getline(fd, line);

    // (u+1) (v+1) weight
    while (std::getline(fd, line)) {
        ss.clear();
        ss.str(line);
        ss >> u >> v >> weight;
        --u;
        --v;
        nEdges++;
        store(u, v, weight);
        // populating caches
        _d[u]++;
        _d[v]++;
        _neighbours[u].push_back(v);
        _neighbours[v].push_back(u);
    }
}

unsigned int Undirected_Weighted_Graph::qtdVertices() const {
    return _m.size();
}

unsigned int Undirected_Weighted_Graph::qtdArestas() const {
    return nEdges;
}

unsigned int Undirected_Weighted_Graph::grau(const unsigned int v) const {
    return _d[v];
}

std::string Undirected_Weighted_Graph::rotulo(const unsigned int v) const {
    return _m[v].first;
}

std::vector<unsigned int> Undirected_Weighted_Graph::vizinhos(const unsigned int v) const {
    return _neighbours[v];
}

bool Undirected_Weighted_Graph::haAresta(const unsigned int u, const unsigned int v) const {
    return peso(u, v) != DEFAULT_EDGE_WEIGHT;
}

float Undirected_Weighted_Graph::peso(const unsigned int u, const unsigned int v) const {
    const unsigned int max = u >= v ? u : v;
    const unsigned int min = u >= v ? v : u;
    return _m.at(min).second[max];
}
