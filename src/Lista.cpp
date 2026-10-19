#include "Lista.h"

template <typename T>
Lista<T>::Lista() {
    capacidade = TAMANHO_INICIAL;
    tamanho = 0;
    itens = new T[capacidade];
}

template <typename T>
Lista<T>::~Lista() {
    delete[] itens;
}

template <typename T>
void Lista<T>::redimensionarLista() {
    int nova_capacidade = capacidade * 2;
    T* novo_vetor = new T[nova_capacidade];

    for (int i = 0; i < tamanho; i++) {
        novo_vetor[i] = itens[i];
    }

    delete[] itens;
    itens = novo_vetor;
    capacidade = nova_capacidade;
}

template <typename T>
int Lista<T>::getTamanho() const { return tamanho; }

template <typename T>
int Lista<T>::getCapacidade() const { return capacidade; }

template <typename T>
T& Lista<T>::getRegistro(int pos) {
    if (pos < 0 || pos >= tamanho) { return nullptr; }
    return itens[pos];
}

template <typename T>
const T& Lista<T>::getRegistro(int pos) const {
    if (pos < 0 || pos >= tamanho) { return nullptr; }
    return itens[pos];
}

template <typename T>
bool Lista<T>::vazia() const { return tamanho == 0; }

template <typename T>
void Lista<T>::limpar() { tamanho = 0; }

template <typename T>
void Lista<T>::insereFinal(const T& item) {
    if (tamanho == capacidade) {
        redimensionarLista();
    }
    itens[tamanho] = item;
    tamanho++;
}