#include "Pilha.h"

Pilha::Pilha() {
    capacidade = TAMANHO_INICIAL;
    tamanho = 0;
    id_itens = new int[capacidade];
}

Pilha::Pilha(const Pilha& outra): id_itens(new int[outra.capacidade]), tamanho(outra.tamanho), capacidade(outra.capacidade) {
    for (int i = 0; i < tamanho; i++) {
        id_itens[i] = outra.id_itens[i];
    }
}

Pilha::~Pilha() { delete[] id_itens; }

Pilha& Pilha::operator=(const Pilha& outra) {
    if (this != &outra) {
        int* novos_itens = new int[outra.capacidade];
        for (int i = 0; i < outra.tamanho; i++) {
            novos_itens[i] = outra.id_itens[i];
        }

        delete[] id_itens;
        id_itens = novos_itens;
        tamanho = outra.tamanho;
        capacidade = outra.capacidade;
    }

    return *this;
}

void Pilha::redimensionarPilha() {
    int nova_capacidade = capacidade * 2;
    int* novo_vetor = new int[nova_capacidade];

    // Copia os elementos existentes para o novo vetor
    for (int i = 0; i < tamanho; i++) {
        novo_vetor[i] = id_itens[i];
    }

    // Libera a memória do vetor antigo e atualiza os atributos
    delete[] id_itens;
    id_itens = novo_vetor;
    capacidade = nova_capacidade;
}

void Pilha::empilhar(int id_item) {
    if (tamanho == capacidade) {
        redimensionarPilha();
    }
    id_itens[tamanho] = id_item;
    tamanho++;
}

int Pilha::desempilhar() {
    if (vazia()) {return -1;}
    tamanho--;
    return id_itens[tamanho];
}

int Pilha::getTamanho() const { return tamanho; }

int Pilha::getTopo() const {
    if (vazia()) {return -1;}
    return id_itens[tamanho - 1];
}

bool Pilha::vazia() const { return tamanho == 0; }

void Pilha::limpar() { tamanho = 0; }
