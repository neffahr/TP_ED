#ifndef PILHA_H
#define PILHA_H

class Pilha {
private:
    int tamanho;
    int* id_itens;          
    int topo;
    
    void redimensionarPilha();

public:
    Pilha(int capacidade_inicial);
    ~Pilha();

    void empilhar(int id_item);
    int desempilhar();

    int getTamanho() const;
    int getTopo() const;
    
    bool vazia() const;
    void limpar();
};

#endif