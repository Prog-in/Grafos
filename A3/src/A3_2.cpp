#include "../../A1/include/A1_1.h"

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using Graph = Undirected_Weighted_Graph;
static constexpr auto inf = std::numeric_limits<float>::max();

bool bfs(Graph &G, std::vector<unsigned int> &M, std::vector<float> &D) {
	std::queue<unsigned int> Q;
	for (unsigned int x = 1; x <= G.qtdVertices() / 2; x++) {
		if (M[x] == 0) {
			D[x] = 0;
			Q.push(x);
		} else {
			D[x] = inf;
		}
	}
	D[0] = inf;
	while (not Q.empty()) {
		unsigned int x = Q.front();
		Q.pop();
		if (D[x] < D[0]) {
			for (unsigned int y : G.vizinhos(x)) {
				if (D[M[y]] == inf) {
					D[M[y]] = D[x] + 1;
					Q.push(M[y]);
				}
			}
		}
	}

	return D[0] != inf;
}

bool dfs(Graph &G, std::vector<unsigned int> &M, unsigned int x, std::vector<float> &D) {
	if (x != 0) {
		for (unsigned int y : G.vizinhos(x)) {
			if (D[M[y]] == D[x] + 1) {
				if (dfs(G, M, M[y], D)) {
					M[x] = y;
					M[y] = x;
					return true;
				}
			}
		}
		D[x] = inf;
		return false;
	}
	return true;
}

void hopcroftKarp(Graph &G) {
	std::vector<float> D(G.qtdVertices() + 1, inf);
	std::vector<unsigned int> M(G.qtdVertices() + 1, 0);
	unsigned int m = 0;

	while (bfs(G, M, D)) {
		for (unsigned int x = 1; x <= G.qtdVertices() / 2; x++) {
			if (M[x] == 0) {
				if (dfs(G, M, x, D)) {
					m += 1;
				}
			}
		}
	}

	std::cout << m << '\n';
	for (unsigned int x = 1; x < G.qtdVertices() / 2; x++) {
		std::cout << x << '-' << M[x] << ", ";
	}
	std::cout << G.qtdVertices() / 2 << '-' << M[G.qtdVertices() / 2] << '\n';

    return;
}

int main(const int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "The program must receive one arguments: the graph file" << std::endl;
        return 1;
    }

    const std::string graphFile = argv[1];
    auto graph = Graph(graphFile);

    hopcroftKarp(graph);

    return 0;
}
