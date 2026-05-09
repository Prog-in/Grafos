#include "../include/A2_Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Directed_Weighted_Graph::store(const unsigned int u, const unsigned int v, const float weight) {
     _m.at(u).second[v] = weight;
}

Directed_Weighted_Graph::Directed_Weighted_Graph(const std::string& arquivo) {
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
        auto row = std::vector<float>(nVertices-i, DEFAULT_EDGE_WEIGHT);
        _m[i] = std::pair("", row);
    }
    _dp = std::vector<unsigned int>(nVertices, 0);
    _dm = std::vector<unsigned int>(nVertices, 0);
    _inNeighbours = std::vector<std::vector<unsigned int>>(nVertices);
    _outNeighbours = std::vector<std::vector<unsigned int>>(nVertices);

    // (i+1) (i+1)_label
    for (unsigned int i = 0; i < nVertices; ++i) {
        unsigned int vertex;
        std::getline(fd, line);
        ss.clear();
        ss.str(line);
        ss >> vertex >> w;
        --vertex;
        _m[vertex].first = w;
        _inNeighbours[vertex] = std::vector<unsigned int>();
        _outNeighbours[vertex] = std::vector<unsigned int>();
    }

    nEdges = 0;
    int u, v;
    float weight;

    // *edges
    std::getline(fd, line);

    // (u+1) (v+1) weight
    while (std::getline(fd, line) and line.size() != 0) {
        ss.clear();
        ss.str(line);
        ss >> u >> v >> weight;
        --u;
        --v;
        nEdges++;
        store(u, v, weight);
        // populating caches
        _dp[u]++;
        _dm[v]++;
        _outNeighbours[u].push_back(v+1);
        _inNeighbours[v].push_back(u+1);
    }
}

unsigned int Directed_Weighted_Graph::qtdVertices() const {
    return _m.size();
}

unsigned int Directed_Weighted_Graph::qtdArestas() const {
    return nEdges;
}

unsigned int Directed_Weighted_Graph::grauMais(const unsigned int v) const {
    return _dp[v-1];
}

unsigned int Directed_Weighted_Graph::grauMenos(const unsigned int v) const {
    return _dm[v-1];
}

std::string& Directed_Weighted_Graph::rotulo(const unsigned int v) {
    return _m[v-1].first;
}

std::vector<unsigned int>& Directed_Weighted_Graph::vizinhosDentro(const unsigned int v) {
    return _inNeighbours[v-1];
}

std::vector<unsigned int>& Directed_Weighted_Graph::vizinhosFora(const unsigned int v) {
    return _outNeighbours[v-1];
}

bool Directed_Weighted_Graph::haAresta(const unsigned int u, const unsigned int v) const {
    return peso(u, v) != DEFAULT_EDGE_WEIGHT;
}

float Directed_Weighted_Graph::peso(const unsigned int u, const unsigned int v) const {
    return _m.at(u).second[v];
}
