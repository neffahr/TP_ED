#include "Pilha.h"

Pilha::Pilha() {
    capacidade = TAMANHO_INICIAL;
    tamanho = 0;
    id_itens = new int[capacidade];
}
Pilha::~Pilha() { delete[] id_itens; }

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
