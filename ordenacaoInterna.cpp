#include "ordenacaoInterna.h"

int particiona(std::vector<Registro>& v, int esquerda, int direita) {
    Registro pivo = v[direita];
    int i = esquerda - 1;

    for (int j = esquerda; j < direita; ++j) {
        if (comparaNota(v[j], pivo)) {
            ++i;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[direita]);
    return i + 1;
}

void quicksort(std::vector<Registro>& v, int esquerda, int direita) {
    if (esquerda < direita) {
        int p = particiona(v, esquerda, direita);
        quicksort(v, esquerda, p - 1);
        quicksort(v, p + 1, direita);
    }
}

void ordenaInternamente(std::vector<Registro>& registros) {
    quicksort(registros, 0, registros.size() - 1);
}
 