#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "registro.h"
#include <string>
#include <vector>

// Lê os primeiros n registros do arquivo com a situação especificada
std::vector<Registro> lerRegistros(const std::string& nomeArquivo, int quantidade, int situacao);

// Escreve um vetor de registros em um arquivo
void escreveRegistros(const std::string& nomeArquivo, const std::vector<Registro>& registros);

// Divide os registros em blocos e escreve em fitas
void geraBlocosOrdenados(const std::vector<Registro>& registros, int numFitas);

// Utilitários para fitas
std::string nomeFitaEntrada(int i);
std::string nomeFitaSaida(int i);

#endif // ARQUIVO_H
  