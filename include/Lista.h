#ifndef LISTA_H
#define LISTA_H

template <typename T>

class Lista {
private:
    T* itens;          // Ponteiro para o vetor dinâmico alocado
    int capacidade;    // Tamanho alocado na memória
    int tamanho;       // Número de elementos armazenados

    void redimensionarLista();

public:
    Lista(int cap_inicial);
    ~Lista();

    int getTamanho() const;
    int getCapacidade() const;
    bool vazia() const;
    void limpar();

    void insereFinal(const T& T);
    T pesquisa(int pos) const;  // TODO: olhar se vai precisar de binária aqui ou coloca em outro canto
    void imprime() const;

};

#endif