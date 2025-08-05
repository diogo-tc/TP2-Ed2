 #ifndef QUICKSORT_EXTERNO_H
#define QUICKSORT_EXTERNO_H

#include <string>

// Aplica Quicksort Externo sobre um arquivo temporário contendo os registros a serem ordenados
void quicksortExterno(const std::string& nomeArquivo, int esq, int dir, int& comparacoes, int& leituras, int& escritas);

#endif // QUICKSORT_EXTERNO_H
