#include "arquivo.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include <algorithm>         
#include "ordenacaoInterna.h" 


std::vector<Registro> lerRegistros(const std::string& nomeArquivo, int quantidade, int situacao) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<Registro> registros;

    std::string linha;
    int lidas = 0;

    while (std::getline(arquivo, linha) && lidas < quantidade) {
        Registro r;
        r.inscricao = std::stol(linha.substr(0, 8));
        r.nota = std::stof(linha.substr(9, 5));
        r.estado = linha.substr(15, 2);
        r.cidade = linha.substr(18, 50);
        r.curso = linha.substr(69, 30);
        registros.push_back(r);
        lidas++;
    }

    if (situacao == 1) {
        std::sort(registros.begin(), registros.end(), comparaNota);
    } else if (situacao == 2) {
        std::sort(registros.begin(), registros.end(), [](const Registro& a, const Registro& b) {
            return a.nota > b.nota;
        });
    }

    return registros;
}

void escreveRegistros(const std::string& nomeArquivo, const std::vector<Registro>& registros) {
    std::ofstream arquivo(nomeArquivo);

    for (const auto& r : registros) {
        arquivo << std::setw(8) << std::setfill('0') << r.inscricao << " "
                << std::fixed << std::setprecision(1) << std::setw(5) << r.nota << " "
                << r.estado << " "
                << r.cidade << " "
                << r.curso << "\n";
    }
}

void geraBlocosOrdenados(const std::vector<Registro>& registros, int numFitas) {
    int tamBloco = 20;
    int totalBlocos = (registros.size() + tamBloco - 1) / tamBloco;

    for (int i = 0; i < totalBlocos; ++i) {
        std::vector<Registro> bloco;
        int ini = i * tamBloco;
        int fim = std::min((i + 1) * tamBloco, (int)registros.size());

        for (int j = ini; j < fim; ++j) {
            bloco.push_back(registros[j]);
        }

        ordenaInternamente(bloco);
        escreveRegistros(nomeFitaEntrada(i), bloco);
    }
}

std::string nomeFitaEntrada(int i) {
    return "fita_in_" + std::to_string(i) + ".txt";
}

std::string nomeFitaSaida(int i) {
    return "fita_out_" + std::to_string(i) + ".txt";
}
