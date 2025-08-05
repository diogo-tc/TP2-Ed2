#include "metodo1.h"
#include "metodo2.h"
#include "metodo3.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: ordena <metodo> <quantidade> <situacao> [-P]\n";
        std::cerr << "  <metodo>: 1, 2 ou 3\n";
        std::cerr << "  <quantidade>: número de registros a serem ordenados\n";
        std::cerr << "  <situacao>: 1 (asc), 2 (desc), 3 (aleatório)\n";
        std::cerr << "  [-P]: opcional, imprime registros ordenados na tela\n";
        return 1;
    }

    int metodo = std::stoi(argv[1]);
    int quantidade = std::stoi(argv[2]);
    int situacao = std::stoi(argv[3]);
    bool imprimir = (argc == 5 && std::string(argv[4]) == "-P");

    switch (metodo) {
        case 1:
            executaMetodo1(quantidade, situacao, imprimir);
            break;
        case 2:
            executaMetodo2(quantidade, situacao, imprimir);
            break;
        case 3:
            executaMetodo3(quantidade, situacao, imprimir);
            break;
            default:
            std::cerr << "Método inválido. Use 1, 2 ou 3.\n";
            return 1;
    }

    return 0;
} 
