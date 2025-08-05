#include "selecaoSubstituicao.h"
#include "ordenacaoInterna.h"
#include "arquivo.h"

#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

struct EntradaHeap {
    Registro reg;
    bool congelado;

    EntradaHeap(const Registro& r) : reg(r), congelado(false) {}

    // Comparação para heap mínimo
    bool operator>(const EntradaHeap& outro) const {
        return reg.nota > outro.reg.nota;
    }
};

void geraBlocosComSelecaoSubstituicao(const std::vector<Registro>& registros, int numFitas) {
    const int TAM_MEMORIA = 20;
    int pos = 0, blocoAtual = 0;

    std::vector<EntradaHeap> area;

    // Pré-carrega a área de seleção
    while (area.size() < TAM_MEMORIA && pos < (int)registros.size()) {
        area.emplace_back(registros[pos++]);
    }

    while (!area.empty()) {
        std::priority_queue<
            EntradaHeap, std::vector<EntradaHeap>, std::greater<EntradaHeap>> heap(area.begin(), area.end());

        std::vector<Registro> bloco;
        Registro ultimoInserido;
        ultimoInserido.nota = -1.0;

        std::vector<EntradaHeap> novaArea;

        while (!heap.empty()) {
            EntradaHeap menor = heap.top();
            heap.pop();

            if (menor.congelado) {
                novaArea.push_back(menor);
                continue;
            }

            bloco.push_back(menor.reg);
            ultimoInserido = menor.reg;

            // Reposição do heap com novo registro, se houver
            if (pos < (int)registros.size()) {
                Registro novo = registros[pos++];
                EntradaHeap novoHeapEntry(novo);

                if (novo.nota < ultimoInserido.nota) {
                    novoHeapEntry.congelado = true; // Vai para o próximo bloco
                    novaArea.push_back(novoHeapEntry);
                } else {
                    heap.push(novoHeapEntry); // Continua no bloco atual
                }
            }
        }

        // Escreve o bloco gerado na fita correspondente
        escreveRegistros(nomeFitaEntrada(blocoAtual % numFitas), bloco);
        blocoAtual++;

        // Prepara a nova área de seleção com registros ainda não processados
        area = novaArea;

        while ((int)area.size() < TAM_MEMORIA && pos < (int)registros.size()) {
            area.emplace_back(registros[pos++]);  
        }
    }
}
