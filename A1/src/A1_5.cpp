//
// Created by Junhaum Hayden on 4/18/26.
//
#include "../include/A1_1.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

const double INF = numeric_limits<double>::max();

void floydWarshall(const Undirected_Weighted_Graph& g, vector<vector<double>>& dist) {
    int n = g.qtdVertices();

    // Initialize distance matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (g.haAresta(i, j)) {
                dist[i][j] = g.peso(i, j);
            } else {
                dist[i][j] = INF;
            }
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }

    string graph_file = argv[1];
    Undirected_Weighted_Graph g(graph_file);

    int n = g.qtdVertices();
    vector<vector<double>> dist(n + 1, vector<double>(n + 1, INF));

    floydWarshall(g, dist);

    // Output the distance matrix
    for (int i = 1; i <= n; i++) {
        cout << i << ":";
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INF) {
                cout << "inf";
            } else {
                cout << fixed << setprecision(0) << dist[i][j];
            }
            if (j < n) cout << ",";
        }
        cout << endl;
    }

    return 0;
}
