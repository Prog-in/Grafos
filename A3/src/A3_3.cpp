// A3_3.cpp
// Implementação do algoritmo exato de Lawler para coloração mínima de vértices.
// Lê um grafo não-dirigido (mesmo formato usado em A2), calcula o número cromático
// e imprime: primeira linha = quantidade de cores utilizadas; segunda linha = cor de cada vértice.

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include "../include/A1_1.h"

int main(int argc, char* argv[]) {
    // Validação básica dos argumentos (arquivo do grafo)
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_grafo>" << std::endl;
        return 1;
    }

    // Construção do objeto grafo a partir do arquivo
    std::string graphFile = argv[1];
    Undirected_Weighted_Graph graph(graphFile);
    int n = static_cast<int>(graph.qtdVertices());

    // Caso base: nenhum vértice
    if (n == 0) {
        std::cout << 0 << std::endl << std::endl;
        return 0;
    }

    // Construção das máscaras de adjacência (bitmasks-operações bitwise)
    std::vector<uint32_t> adj(n, 0);
    for (int u = 1; u <= n; ++u) {
        for (unsigned int v : graph.vizinhos(u)) {
            if (v >= 1 && v <= (unsigned int)n) {
                // converte índices 1-based do grafo para 0-based na máscara
                adj[u - 1] |= (1u << (v - 1));
            }
        }
    }

    // Número total de subconjuntos de vértices: 2^n
    const int N = 1 << n;

    // independent[mask] = 1 se o subconjunto 'mask' for um conjunto independente (sem arestas internas)
    std::vector<char> independent(N, 0);

    // Pré-computar quais subconjuntos são independentes.
    for (int mask = 1; mask < N; ++mask) {
        bool ok = true;
        int m = mask;
        while (m) {
            int v = __builtin_ctz(m); // índice do primeiro bit ligado
            m &= (m - 1); // remove esse bit
            // Se algum vizinho de v estiver também em 'mask', então não é independente
            if (adj[v] & mask) {
                ok = false;
                break;
            }
        }
        independent[mask] = ok ? 1 : 0;
    }

    // Programação dinâmica (Lawler):
    std::vector<int> chi(N, n + 1);
    std::vector<int> parent(N, 0);
    chi[0] = 0;

    // Para cada subconjunto S, enumerar seus submasks I (non-empty) e atualizar chi[S]
    for (int S = 1; S < N; ++S) {
        // Enumerar todos os submasks I de S: for(I = S; I; I = (I-1)&S)
        for (int I = S; I; I = (I - 1) & S) {
            if (!independent[I]) continue; // só interessa conjuntos independentes
            int cand = 1 + chi[S ^ I]; // colorir I com uma nova cor + o resto
            if (cand < chi[S]) {
                chi[S] = cand;
                parent[S] = I; // armazenar a escolha para reconstrução
                if (chi[S] == 1) break; // limite inferior para S (melhor possível)
            }
        }
    }

    int all = N - 1; // máscara com todos os vértices
    int colorsUsed = chi[all];
    std::cout << colorsUsed << std::endl;

    // Reconstrução da coloração a partir de parent[]:
    // Percorre os conjuntos independentes escolhidos e atribui IDs de cor incrementais.
    std::vector<int> color(n, 0);
    int S = all;
    int colorId = 1;
    while (S) {
        int I = parent[S];
        for (int i = 0; i < n; ++i) {
            if (I & (1 << i)) color[i] = colorId;
        }
        colorId++;
        S ^= I; // remover I de S
    }

    // Impressão das cores por vértice no formato pedido: "c1, c2, ..., cn"
    for (int i = 0; i < n; ++i) {
        std::cout << color[i];
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    return 0;
}
