#include "metodo2.h"
#include "selecaoSubstituicao.h"
#include "arquivo.h"
#include <iostream>
#include <chrono>
#include <queue>
#include <fstream>

struct Fita {
    std::ifstream entrada;
    Registro atual;
    bool fim;

    Fita(const std::string& nome) : entrada(nome), fim(false) {
        avancar();
    }

    void avancar() {
        std::string linha;
        if (std::getline(entrada, linha)) {
            atual.inscricao = std::stol(linha.substr(0, 8));
            atual.nota = std::stof(linha.substr(9, 5));
            atual.estado = linha.substr(15, 2);
            atual.cidade = linha.substr(18, 50);
            atual.curso = linha.substr(69, 30);
        } else {
            fim = true;
        }
    }

    bool operator>(const Fita& outra) const {
        return atual.nota > outra.atual.nota;
    }
};

void executaMetodo2(int quantidade, int situacao, bool imprimir) {
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();

    auto registros = lerRegistros("PROVAO.TXT", quantidade, situacao);

    geraBlocosComSelecaoSubstituicao(registros, 20);

    int numFitasEntrada = (quantidade + 19) / 20;
    std::vector<Fita*> fitas;

    for (int i = 0; i < numFitasEntrada; ++i) {
        fitas.push_back(new Fita(nomeFitaEntrada(i)));
    }

    auto comp = [](Fita* a, Fita* b) { return a->atual.nota > b->atual.nota; };
    std::priority_queue<Fita*, std::vector<Fita*>, decltype(comp)> fila(comp);

    for (auto* fita : fitas) {
        if (!fita->fim) fila.push(fita);
    }

    std::vector<Registro> resultado;
    int comparacoes = 0, leituras = 0, escritas = 0;

    while (!fila.empty()) {
        auto* menor = fila.top(); fila.pop();
        resultado.push_back(menor->atual);
        escritas++;
        menor->avancar(); leituras++;
        comparacoes++;
        if (!menor->fim) fila.push(menor);
    }

    auto fim = high_resolution_clock::now();
    double tempo = duration_cast<duration<double>>(fim - inicio).count();

    escreveRegistros("resultado.txt", resultado);

    if (imprimir) {
        for (const auto& r : resultado) {
            std::cout << r.inscricao << " " << r.nota << " " << r.estado << " "
                      << r.cidade << " " << r.curso << "\n";
        }
    }

    std::cout << "\n--- MÉTODO 2 ---\n";
    std::cout << "Comparações: " << comparacoes << "\n";
    std::cout << "Leituras: " << leituras << "\n";
    std::cout << "Escritas: " << escritas << "\n";
    std::cout << "Tempo de execução: " << tempo << " segundos\n";

    for (auto* f : fitas) delete f;
}
