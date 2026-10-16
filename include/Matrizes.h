#ifndef MATRIZES_H
#define MATRIZES_H

class Matriz {
protected:
    int l; // Número de linhas
    int c; // Número de colunas

public:
    Matriz(int linhas, int colunas);
    virtual ~Matriz();

    // Leituras e escritas
    virtual double Get(int i, int j) const = 0;
    virtual void Set(int i, int j, double v) = 0;
    virtual void Imprime() const = 0;
};


class MatrizCOO : public Matriz {
private:
    int tamanho;
    int tamanhoMAX; // capacidade dos vetores
    int* linhas;
    int* colunas;
    double* valores;

    void InsereElemento(int i, int j, double v);
    void RemoveElemento(int p);
    void Cresce();

public:
    MatrizCOO(int linhas, int colunas);
    virtual ~MatrizCOO() override;

    double Get(int i, int j) const override;
    void Set(int i, int j, double v) override;
    
    static void Soma(const MatrizCOO& A, const MatrizCOO& B, MatrizCOO& C);
    static double* Produto(const MatrizCOO& A, const double* u, int n);
};


struct Celula {
    int lin, col;
    double val;
    Celula* proxLin; // proxima celula na mesma linha (coluna maior)
    Celula* proxCol; // proxima celula na mesma coluna (linha maior)
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

    double Get(int i, int j) const override;
    void Set(int i, int j, double v) override;
    
    double SomaColuna(int j) const;
    static double* Produto(const MatrizEncadeada& A, const double* u, int n);
};

#endif