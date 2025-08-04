#include "selecaoSubstituicao.h"
#include "ordenacaoInterna.h"
#include "arquivo.h"

#include <queue>
#include <fstream>

struct EntradaHeap {
    Registro reg;
    bool congelado;

    EntradaHeap(const Registro& r) : reg(r), congelado(false) {}

    // Operador de comparação para heap mínimo
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

        while (!heap.empty()) {
            EntradaHeap menor = heap.top();
            heap.pop();

            if (menor.congelado) continue;

            bloco.push_back(menor.reg);
            ultimoInserido = menor.reg;

            // Reposição do heap com novo registro, se houver
            if (pos < (int)registros.size()) {
                Registro novo = registros[pos++];
                if (novo.nota < ultimoInserido.nota) {
                    heap.push(EntradaHeap(novo)); // congela no próximo bloco
                    heap.top().congelado = true;
                } else {
                    heap.push(EntradaHeap(novo));
                }
            }
        }

        escreveRegistros(nomeFitaEntrada(blocoAtual), bloco);
        blocoAtual++;

        // Recarrega área com registros ainda não processados
        area.clear();
        for (int i = pos; i < std::min(pos + TAM_MEMORIA, (int)registros.size()); ++i) {
            area.emplace_back(registros[i]);
        }
        pos += TAM_MEMORIA;
    }
}
