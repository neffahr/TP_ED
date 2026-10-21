#ifndef MATRIZENCADEADA_H
#define MATRIZENCADEADA_H

#include "Matriz.h"

struct Celula {
    int lin, col;
    int val;
    Celula* proxLin; // proxima celula na mesma linha
    Celula* proxCol; // proxima celula na mesma coluna
};

class MatrizEncadeada : public Matriz {
private:
    int tamanho;
    Celula** cabLin; // celula cabeca da linha i
    Celula** cabCol; // celula cabeca da coluna j

    Celula* AntLinha(int i, int j) const;
    Celula* AntColuna(int i, int j) const;

public:
    MatrizEncadeada(int linhas, int colunas);
    virtual ~MatrizEncadeada() override;

    int Get(int i, int j) const override;
    void Set(int i, int j, int v) override;

    int getLinha(int i, int*& cols, int*& modificadores) const override;
    void redimencionarMatriz(int l, int c) override;
    int somarLinha(int i) const override;
};

#endif