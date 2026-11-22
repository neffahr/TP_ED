#ifndef CONJUNTOS_DISJUNTOS_H
#define CONJUNTOS_DISJUNTOS_H

class ConjuntosDisjuntos {
private:
    int* pai;
    int* rank;
    int num_conjuntos;
    int tamanho;
    int capacidade;

    static const int CAPACIDADE_INICIAL = 16;

    // Dobra a capacidade dos vetores dinâmicos quando novas regiões são cadastradas
    void redimensionar(int nova_capacidade);

public:
    ConjuntosDisjuntos(int capacidade_inicial = CAPACIDADE_INICIAL);
    ~ConjuntosDisjuntos();

    void Make(int x);
    int Find(int x);
    void Union(int x, int y);
    
    bool conectados(int x, int y);

    // Consultores auxiliares
    int getNumConjuntos() const { return num_conjuntos; }
    int getTamanho() const { return tamanho; }
};

#endif