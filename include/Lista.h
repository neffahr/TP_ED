#ifndef LISTA_H
#define LISTA_H

template <typename T>

class Lista {
private:
    T* itens;          // Ponteiro para o vetor dinâmico alocado
    int tamanho;       // Número de elementos armazenados
    int capacidade;    // Tamanho alocado na memória

    static const int TAMANHO_INICIAL = 10;

    void redimensionarLista();

public:
    Lista();
    ~Lista();

    int getTamanho() const;
    int getCapacidade() const;
    T& getRegistro(int pos);
    bool vazia() const;
    void limpar();

    void insereFinal(const T& item);
    T pesquisa(int pos) const;  // TODO: olhar se vai precisar de binária aqui ou coloca em outro canto
    void imprime() const;

};

#endif