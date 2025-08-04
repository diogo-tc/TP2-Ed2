#include "ordenacaoInterna.h"
#include <algorithm>

void ordenaInternamente(std::vector<Registro>& registros) {
    std::sort(registros.begin(), registros.end(), comparaNota);
}
