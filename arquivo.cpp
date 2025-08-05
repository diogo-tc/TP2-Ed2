#include "include/arquivo.h"
#include "include/ordenacaoInterna.h" 
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include <algorithm>         
using namespace std;


vector<Registro> lerRegistros(const string& nomeArquivo, int quantidade, int situacao) {
    ifstream arquivo(nomeArquivo);
    vector<Registro> registros;
   
    string linha;
    int lidas = 0;

    while (getline(arquivo, linha) && lidas < quantidade) {
        Registro r;
        r.inscricao = stol(linha.substr(0, 8));
        r.nota = stof(linha.substr(9, 5));
        r.estado = linha.substr(15, 2);
        r.cidade = linha.substr(18, 50);
        r.curso = linha.substr(69, 30);
        registros.push_back(r);
        lidas++;
    }

    if (situacao == 1) {
        sort(registros.begin(), registros.end(), comparaNota);
    } else if (situacao == 2) {
        sort(registros.begin(), registros.end(), [](const Registro& a, const Registro& b) {
            return a.nota > b.nota;
        });
    }

    return registros;
}

void escreveRegistros(const string& nomeArquivo, const vector<Registro>& registros) {
    ofstream arquivo(nomeArquivo);

    for (const auto& r : registros) {
        arquivo << setw(8) << setfill('0') << r.inscricao << " "
                << fixed << setprecision(1) << setw(5) << r.nota << " "
                << r.estado << " "
                << r.cidade << " "
                << r.curso << "\n";
    }
}

void geraBlocosOrdenados(const vector<Registro>& registros, int numFitas) {
    int tamBloco = 20;
    int totalBlocos = (registros.size() + tamBloco - 1) / tamBloco;

    for (int i = 0; i < totalBlocos; ++i) {
        vector<Registro> bloco;
        int ini = i * tamBloco;
        int fim = min((i + 1) * tamBloco, (int)registros.size());

        for (int j = ini; j < fim; ++j) {
            bloco.push_back(registros[j]);
        }

        ordenaInternamente(bloco);
        escreveRegistros(nomeFitaEntrada(i), bloco);
    }
}

string nomeFitaEntrada(int i) {
    return "fita_in_" + to_string(i) + ".txt";
}

string nomeFitaSaida(int i) {
    return "fita_out_" + to_string(i) + ".txt";
}
