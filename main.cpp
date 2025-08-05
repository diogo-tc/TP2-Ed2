#include "include/metodo1.h"
#include "include/metodo2.h"
#include "include/metodo3.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: ordena <metodo> <quantidade> <situacao> [-P]\n";
        cerr << "  <metodo>: 1, 2 ou 3\n";
        cerr << "  <quantidade>: número de registros a serem ordenados\n";
        cerr << "  <situacao>: 1 (asc), 2 (desc), 3 (aleatório)\n";
        cerr << "  [-P]: opcional, imprime registros ordenados na tela\n";
        return 1;
    }

    int metodo = stoi(argv[1]);
    int quantidade = stoi(argv[2]);
    int situacao = stoi(argv[3]);
    bool imprimir = (argc == 5 && string(argv[4]) == "-P");

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
            cerr << "Método inválido. Use 1, 2 ou 3.\n";
            return 1;
    }

    return 0;
}  
