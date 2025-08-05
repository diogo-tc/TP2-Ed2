#include "quicksortExterno.h"
#include "registro.h"
#include "arquivo.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
  

void quicksortExterno(const std::string& nomeArquivo, int esq, int dir,
                      int& comparacoes, int& leituras, int& escritas) {
    if (esq >= dir) return;

    // Leitura de até 20 registros entre esq e dir
    std::ifstream arq(nomeArquivo);
    std::vector<Registro> memoria;

    int total = dir - esq + 1;
    int qtdLer = std::min(20, total);
    int linhaAtual = 0;

    std::string linha;
    while (std::getline(arq, linha) && (int)memoria.size() < qtdLer) {
        if (linhaAtual >= esq && linhaAtual <= dir) {
            Registro r;
            r.inscricao = std::stol(linha.substr(0, 8));
            r.nota = std::stof(linha.substr(9, 5));
            r.estado = linha.substr(15, 2);
            r.cidade = linha.substr(18, 50);
            r.curso = linha.substr(69, 30);
            memoria.push_back(r);
            leituras++;
        }
        linhaAtual++;
    }

    // Usa o último elemento como pivô
    Registro pivo = memoria.back();
    comparacoes++;

    std::vector<Registro> menores, maiores;

    for (int i = 0; i < (int)memoria.size() - 1; ++i) {
        comparacoes++;
        if (memoria[i].nota < pivo.nota)
            menores.push_back(memoria[i]);
        else
            maiores.push_back(memoria[i]);
    }

    // Junta partições
    std::vector<Registro> resultado = menores;
    resultado.push_back(pivo);
    resultado.insert(resultado.end(), maiores.begin(), maiores.end());

    // Escreve no mesmo arquivo, sobrescrevendo as linhas [esq..dir]
    std::ifstream original(nomeArquivo);
    std::ofstream temp("temp.txt");
    linhaAtual = 0;
    int iRes = 0;

    while (std::getline(original, linha)) {
        if (linhaAtual >= esq && linhaAtual <= dir && iRes < (int)resultado.size()) {
            const Registro& r = resultado[iRes++];
            temp << std::setw(8) << std::setfill('0') << r.inscricao << " "
                 << std::fixed << std::setprecision(1) << std::setw(5) << r.nota << " "
                 << r.estado << " "
                 << r.cidade << " "
                 << r.curso << "\n";
            escritas++;
        } else {
            temp << linha << "\n";
        }
        linhaAtual++;
    }

    original.close();
    temp.close();

    std::remove(nomeArquivo.c_str());
    std::rename("temp.txt", nomeArquivo.c_str());

    int meio = esq + menores.size();
    quicksortExterno(nomeArquivo, esq, meio - 1, comparacoes, leituras, escritas);
    quicksortExterno(nomeArquivo, meio + 1, dir, comparacoes, leituras, escritas);
}
