#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz {
protected:
    int l; // Número de linhas
    int c; // Número de colunas

public:
    Matriz(int linhas, int colunas) : l(linhas), c(colunas) {}
    virtual ~Matriz() {}

    // Leituras e escritas
    virtual int Get(int i, int j) const = 0;
    virtual void Set(int i, int j, int v) = 0;
    
    virtual int getLinha(int i, int*& cols, int*& modificadores) const = 0;
    virtual int getColuna(int j, int*& linhas, int*& modificadores) const = 0;

    virtual void redimencionarMatriz(int l, int c) = 0;
    virtual int somarLinha(int i) const = 0;
};

#endif