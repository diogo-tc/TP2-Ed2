#include "metodo3.h"
#include "quicksortExterno.h"
#include "arquivo.h"
#include "registro.h"

#include <iostream>
#include <chrono>
#include <fstream> 
#include <vector>

void executaMetodo3(int quantidade, int situacao, bool imprimir) {
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();

    auto registros = lerRegistros("PROVAO.TXT", quantidade, situacao); 
    std::string nomeTemp = "quicksort_temp.txt";
    escreveRegistros(nomeTemp, registros);

    int comparacoes = 0, leituras = 0, escritas = 0;
    quicksortExterno(nomeTemp, 0, quantidade - 1, comparacoes, leituras, escritas);

    std::vector<Registro> resultado = lerRegistros(nomeTemp, quantidade, 1); // já ordenado ascendente

    auto fim = high_resolution_clock::now();
    double tempo = duration_cast<duration<double>>(fim - inicio).count();

    escreveRegistros("resultado.txt", resultado);

    if (imprimir) {
        for (const auto& r : resultado) {
            std::cout << r.inscricao << " " << r.nota << " " << r.estado << " "
                      << r.cidade << " " << r.curso << "\n";
        }
    }

    std::cout << "\n--- MÉTODO 3 ---\n";
    std::cout << "Comparações: " << comparacoes << "\n";
    std::cout << "Leituras: " << leituras << "\n";
    std::cout << "Escritas: " << escritas << "\n";
    std::cout << "Tempo de execução: " << tempo << " segundos\n";
}
