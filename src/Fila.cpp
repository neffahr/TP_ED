#include "Fila.h"

Fila::Fila() {
    frente = new NoFila();
    frente->prox = nullptr;
    tras = frente;
    tamanho = 0;
}

Fila::~Fila() {
    limpar();
    delete frente; // Deleta a célula cabeça remanescente
}

int Fila::getTamanho() const { return tamanho; }

void Fila::enfileirar(int id_aventureiro, int id_item) {
    NoFila* nova = new NoFila();
    nova->encomenda.id_aventureiro = id_aventureiro;
    nova->encomenda.id_item = id_item;
    nova->prox = nullptr;

    tras->prox = nova;
    tras = nova;
    tamanho++;
}

Encomenda Fila::desenfileirar() {
    Encomenda aux = frente->prox->encomenda;
    NoFila* p = frente;
    frente = frente->prox;
    delete p;

    tamanho--;
    return aux;
}

bool Fila::vazia() const { return tamanho == 0; }

void Fila::limpar() {
    NoFila* p = frente->prox;
    while (p != nullptr) {
        frente->prox = p->prox;
        delete p;
        p = frente->prox;
    }
    tamanho = 0;
    tras = frente;
}