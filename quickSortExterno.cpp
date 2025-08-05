#include "include/quicksortExterno.h"
#include "include/registro.h"
#include "include/arquivo.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void quicksortExterno(const string& nomeArquivo, int esq, int dir,
                      int& comparacoes, int& leituras, int& escritas) {
    if (esq >= dir) return;

    // Leitura de até 20 registros entre esq e dir
    ifstream arq(nomeArquivo);
    vector<Registro> memoria;

    int total = dir - esq + 1;
    int qtdLer = min(20, total);
    int linhaAtual = 0;

    string linha;
    while (getline(arq, linha) && (int)memoria.size() < qtdLer) {
        if (linhaAtual >= esq && linhaAtual <= dir) {
            Registro r;
            r.inscricao = stol(linha.substr(0, 8));
            r.nota = stof(linha.substr(9, 5));
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

    vector<Registro> menores, maiores;

    for (int i = 0; i < (int)memoria.size() - 1; ++i) {
        comparacoes++;
        if (memoria[i].nota < pivo.nota)
            menores.push_back(memoria[i]);
        else
            maiores.push_back(memoria[i]);
    }

    // Junta partições
    vector<Registro> resultado = menores;
    resultado.push_back(pivo);
    resultado.insert(resultado.end(), maiores.begin(), maiores.end());

    // Escreve no mesmo arquivo, sobrescrevendo as linhas [esq..dir]
    ifstream original(nomeArquivo);
    ofstream temp("temp.txt");
    linhaAtual = 0;
    int iRes = 0;

    while (getline(original, linha)) {
        if (linhaAtual >= esq && linhaAtual <= dir && iRes < (int)resultado.size()) {
            const Registro& r = resultado[iRes++];
            temp << setw(8) << setfill('0') << r.inscricao << " "
                 << fixed << setprecision(1) << setw(5) << r.nota << " "
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

    remove(nomeArquivo.c_str());
    rename("temp.txt", nomeArquivo.c_str());

    int meio = esq + menores.size();
    quicksortExterno(nomeArquivo, esq, meio - 1, comparacoes, leituras, escritas);
    quicksortExterno(nomeArquivo, meio + 1, dir, comparacoes, leituras, escritas);
}
