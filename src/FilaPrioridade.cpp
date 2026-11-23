#include "FilaPrioridade.h"
#include <stdexcept>

FilaPrioridade::FilaPrioridade(int capacidade) {
    this->capacidade = (capacidade > 0) ? capacidade : TAMANHO_INICIAL;
    this->tamanho = 0;
    this->v = new NoHeap[this->capacidade];
}

FilaPrioridade::~FilaPrioridade() { delete[] v; }

void FilaPrioridade::Redimensionar() {
    int nova_capacidade = capacidade * 2;
    NoHeap* novo_v = new NoHeap[nova_capacidade];

    for (int i = 0; i < tamanho; i++) {
        novo_v[i] = v[i];
    }

    delete[] v;
    v = novo_v;
    capacidade = nova_capacidade;
}

bool FilaPrioridade::vemAntes(const NoHeap& a, const NoHeap& b) const {
    if (a.prioridade != b.prioridade) {
        return a.prioridade > b.prioridade;
    }
    return a.id_cliente < b.id_cliente;
}


void FilaPrioridade::Sobe(int i) {
    while (i > 0) {
        int p = GetAncestral(i);
        if (vemAntes(v[i], v[p])) {
            NoHeap aux = v[i];
            v[i] = v[p];
            v[p] = aux;
            i = p;
        } else {
            return;
        }
    }
}

void FilaPrioridade::Desce(int i) {
    while (true) {
        int e = GetSucessorEsq(i);
        int d = GetSucessorDir(i);
        int maior = i;

        if (e < tamanho && vemAntes(v[e], v[maior])) 
            maior = e;
        if (d < tamanho && vemAntes(v[d], v[maior]))
            maior = d;

        if (maior == i) return;

        NoHeap aux = v[i];
        v[i] = v[maior];
        v[maior] = aux;
        i = maior;
    }
}


void FilaPrioridade::Insere(int id_cliente, int prioridade) {
    if (tamanho == capacidade) Redimensionar();

    v[tamanho].id_cliente = id_cliente;
    v[tamanho].prioridade = prioridade;
    tamanho++;

    Sobe(tamanho - 1);
}

NoHeap FilaPrioridade::Remove() {
    NoHeap x = v[0];
    v[0] = v[tamanho - 1];
    tamanho--;

    if (tamanho > 0) Desce(0);

    return x;
}

NoHeap FilaPrioridade::Maximo() const { return v[0]; }