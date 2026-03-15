#ifndef GRAFOS_UTILS_H
#define GRAFOS_UTILS_H
#include <iostream>
#include <ostream>
#include <vector>

template <typename T>
void printVector(std::vector<T>& vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

template <typename T>
void printMatrix(std::vector<std::vector<T>>& vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        printVector(vec[i]);
    }
}

#endif //GRAFOS_UTILS_H