#include "MatrizEncadeada.h"

MatrizEncadeada::MatrizEncadeada(int linhas, int colunas) : Matriz(linhas, colunas) {
    tamanho = 0;
    cabLin = new Celula*[l];
    cabCol = new Celula*[c];

    for (int i = 0; i < l; i++) {
        cabLin[i] = new Celula{i, -1, 0, nullptr, nullptr};
    }
    
    for (int j = 0; j < c; j++) {
        cabCol[j] = new Celula{-1, j, 0, nullptr, nullptr};
    }
}

MatrizEncadeada::~MatrizEncadeada() {
    for (int i = 0; i < l; i++) {
        Celula* p = cabLin[i];
        while (p != nullptr) {
            Celula* q = p->proxLin;
            delete p;
            p = q;
        }
    }

    for (int j = 0; j < c; j++) { delete cabCol[j]; }
    delete[] cabLin;
    delete[] cabCol;
}

Celula* MatrizEncadeada::AntLinha(int i, int j) const {
    Celula* p = cabLin[i];
    while (p->proxLin != nullptr && p->proxLin->col < j) {
        p = p->proxLin;
    }
    return p;
}

Celula* MatrizEncadeada::AntColuna(int i, int j) const {
    Celula* p = cabCol[j];
    while (p->proxCol != nullptr && p->proxCol->lin < i) {
        p = p->proxCol;
    }
    return p;
}

int MatrizEncadeada::Get(int i, int j) const {
    if (i < 0 || i >= l || j < 0 || j >= c) {
        return 0;
    }
    
    Celula* ant = AntLinha(i, j);
    Celula* p = ant->proxLin;
    
    if (p != nullptr && p->col == j) {
        return p->val;
    }
    return 0;
}

void MatrizEncadeada::Set(int i, int j, int v) {
    if (i < 0 || i >= l || j < 0 || j >= c) {
        throw "Posicao invalida";
    }
    
    Celula* antL = AntLinha(i, j);
    Celula* antC = AntColuna(i, j);
    Celula* p = antL->proxLin;

    if (p != nullptr && p->col == j) {
        if (v != 0) {
            p->val = v; 
            return;
        }
        antL->proxLin = p->proxLin;
        antC->proxCol = p->proxCol;
        delete p;
        tamanho--;
        return;
    }
    if (v == 0) return;
    Celula* nova = new Celula{i, j, v, antL->proxLin, antC->proxCol};

    antL->proxLin = nova;
    antC->proxCol = nova;
    tamanho++;
}

int MatrizEncadeada::getLinha(int i, int*& cols, int*& modificadores) const {
    if (i < 0 || i >= l) throw "Posicao invalida";

    int qtd = 0;
    Celula* p = cabLin[i]->proxLin;
    while (p != nullptr) {
        qtd++;
        p = p->proxLin;
    }

    if (qtd == 0) {
        cols = nullptr;
        modificadores = nullptr;
        return 0;
    }

    cols = new int[qtd];
    modificadores = new int[qtd];

    p = cabLin[i]->proxLin;
    int idx = 0;
    while (p != nullptr) {
        cols[idx] = p->col;
        modificadores[idx] = p->val;
        p = p->proxLin;
        idx++;
    }
    
    return qtd;
}

void MatrizEncadeada::redimencionarMatriz(int l, int c) {

}

int MatrizEncadeada::somarLinha(int i) const {
    int soma = 0;
    Celula* p = cabLin[i]->proxLin;
    
    while (p != nullptr) {
        soma += p->val;
        p = p->proxLin;
    }
    return soma;
}