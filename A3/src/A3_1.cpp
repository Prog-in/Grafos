#include "../../A2/include/A2_Graph.h"

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

// BFS to find an augmenting path in the residual graph.
// Returns true if there is a path from s to t, and fills 'parent'
// with the predecessor of each vertex along that path.
bool bfs(const unsigned int n, const std::vector<std::vector<float>>& residual, const unsigned int s,
        const unsigned int t, std::vector<int>& parent) {
    std::fill(parent.begin(), parent.end(), -1);
    parent[s] = static_cast<int>(s);

    std::queue<unsigned int> q;
    q.push(s);

    while (!q.empty()) {
        const unsigned int u = q.front();
        q.pop();

        for (unsigned int v = 0; v < n; ++v) {
            if (parent[v] == -1 && residual[u][v] > 0.0f) {
                parent[v] = static_cast<int>(u);
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

float edmondsKarp(Directed_Weighted_Graph& graph, const unsigned int s, const unsigned int t) {
    const unsigned int n = graph.qtdVertices();

    // Build the residual capacity matrix (0-indexed internally).
    // Forward edges come from the graph weights; backward edges start at 0.
    std::vector<std::vector<float>> residual(n, std::vector<float>(n, 0.0f));

    for (unsigned int u = 1; u <= n; ++u) {
        for (const unsigned int v : graph.vizinhosFora(u)) {
            // graph uses 1-indexed vertices; matrix is 0-indexed
            residual[u - 1][v - 1] += graph.peso(u - 1, v - 1); // peso() is 0-indexed internally
        }
    }

    float maxFlow = 0.0f;
    std::vector<int> parent(n);

    // Augment while there is a path from s to t in the residual graph
    while (bfs(n, residual, s - 1, t - 1, parent)) {
        // Find the bottleneck along the path found by BFS
        float pathFlow = std::numeric_limits<float>::max();
        for (unsigned int v = t - 1; v != s - 1; ) {
            const unsigned int u = static_cast<unsigned int>(parent[v]);
            pathFlow = std::min(pathFlow, residual[u][v]);
            v = u;
        }

        // Update residual capacities (forward and backward edges)
        for (unsigned int v = t - 1; v != s - 1; ) {
            const unsigned int u = static_cast<unsigned int>(parent[v]);
            residual[u][v] -= pathFlow;
            residual[v][u] += pathFlow;
            v = u;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main(const int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "The program must receive three arguments: the graph file, the origin and the destination" << std::endl;
        return 1;
    }

    const std::string graphFile = argv[1];
    const unsigned int s = static_cast<unsigned int>(std::stoul(argv[2]));
    const unsigned int t = static_cast<unsigned int>(std::stoul(argv[3]));

    auto graph = Directed_Weighted_Graph(graphFile);

    const float result = edmondsKarp(graph, s, t);

    // Print as integer if the value is a whole number, otherwise as float
    if (result == static_cast<float>(static_cast<long long>(result))) {
        std::cout << static_cast<long long>(result) << '\n';
    } else {
        std::cout << result << '\n';
    }

    return 0;
}