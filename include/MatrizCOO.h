#ifndef MATRIZCOO_H
#define MATRIZCOO_H

#include "Matriz.h"

class MatrizCOO : public Matriz {
private:
    int tamanho;
    int tamanhoMAX; // capacidade dos vetores
    int* linhas;
    int* colunas;
    int* valores;

    void InsereElemento(int i, int j, int v);
    void RemoveElemento(int p);
    void Cresce();

public:
    MatrizCOO(int linhas, int colunas);
    virtual ~MatrizCOO() override;

    int Get(int i, int j) const override;
    void Set(int i, int j, int v) override;
    int getLinha(int i, int*& cols, int*& modificadores) const override;
    void redimencionarMatriz(int l, int c) override;
    int somarLinha(int i) const override;
};

#endif