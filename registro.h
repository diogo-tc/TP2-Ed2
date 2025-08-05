#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

struct Registro {
    long inscricao;
    float nota;
    std::string estado;
    std::string cidade;
    std::string curso;
};

// Função de comparação por nota
bool comparaNota(const Registro& a, const Registro& b);

#endif // REGISTRO_H

  