#include "include/metodo3.h"
#include "include/quicksortExterno.h"
#include "include/arquivo.h"
#include "include/registro.h"

#include <iostream>
#include <chrono>
#include <fstream> 
#include <vector>

using namespace std;

void executaMetodo3(int quantidade, int situacao, bool imprimir) {
    using namespace chrono;
    auto inicio = high_resolution_clock::now();

    auto registros = lerRegistros("PROVAO.TXT", quantidade, situacao); 
    string nomeTemp = "quicksort_temp.txt";
    escreveRegistros(nomeTemp, registros);

    int comparacoes = 0, leituras = 0, escritas = 0;
    quicksortExterno(nomeTemp, 0, quantidade - 1, comparacoes, leituras, escritas);

    vector<Registro> resultado = lerRegistros(nomeTemp, quantidade, 1); // já ordenado ascendente

    auto fim = high_resolution_clock::now();
    double tempo = duration_cast<duration<double>>(fim - inicio).count();

    escreveRegistros("resultado.txt", resultado);

    if (imprimir) {
        for (const auto& r : resultado) {
            cout << r.inscricao << " " << r.nota << " " << r.estado << " "
                      << r.cidade << " " << r.curso << "\n";
        }
    }

    cout << "\n--- MÉTODO 3 ---\n";
    cout << "Comparações: " << comparacoes << "\n";
    cout << "Leituras: " << leituras << "\n";
    cout << "Escritas: " << escritas << "\n";
    cout << "Tempo de execução: " << tempo << " segundos\n";
}
