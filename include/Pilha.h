#ifndef PILHA_H
#define PILHA_H

class Pilha {
private:
    int* id_itens;          
    int tamanho;
    int capacidade;

    static const int TAMANHO_INICIAL = 5;
    
    void redimensionarPilha();

public:
    Pilha();
    Pilha(const Pilha& outra);
    ~Pilha();

    Pilha& operator=(const Pilha& outra);

    void empilhar(int id_item);
    int desempilhar();

    int getTamanho() const;
    int getTopo() const;
    
    bool vazia() const;
    void limpar();
};

#endif