#ifndef FILA_H
#define FILA_H

struct Encomenda {
    int id_aventureiro;
    int id_item;
};

struct NoFila {
    Encomenda encomenda;
    NoFila* prox;
};

class Fila {
private:
    NoFila* frente;
    NoFila* tras;
    int tamanho;

public:
    Fila();
    ~Fila();

    int getTamanho() const;
    void enfileirar(int id_aventureiro, int id_item);
    Encomenda desenfileirar();
    bool vazia() const;
    void limpar();
};

#endif