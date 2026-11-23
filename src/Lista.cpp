#include "Lista.h"
#include "Cliente.h"
#include "EstruturaIndice.h"

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
    if (pos < 0 || pos >= tamanho) { throw "Posicao da lista invalida"; }
    return itens[pos];
}

template <typename T>
const T& Lista<T>::getRegistro(int pos) const {
    if (pos < 0 || pos >= tamanho) { throw "Posicao da lista invalida"; }
    return itens[pos];
}

template <typename T>
void Lista<T>::insereFinal(const T& item) {
    if (tamanho == capacidade) {
        redimensionarLista();
    }
    itens[tamanho] = item;
    tamanho++;
}

// Insertion Sort
template <typename T>
void Lista<T>::ordenar() {
    for (int i = 1; i < tamanho; i++) {
        T chave = itens[i];
        int j = i - 1;

        while (j >= 0 && chave < itens[j]) {
            itens[j + 1] = itens[j];
            j--;
        }

        itens[j + 1] = chave;
    }
}

template <typename T>
bool Lista<T>::vazia() const { return tamanho == 0; }

template class Lista<Cliente>;
template class Lista<DadoIndice>;