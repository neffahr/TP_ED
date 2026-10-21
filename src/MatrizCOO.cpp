#include "MatrizCOO.h"

MatrizCOO::MatrizCOO(int linhas_, int colunas_) : Matriz(linhas_, colunas_) {
    tamanho = 0;
    tamanhoMAX = 4;
    linhas = new int[tamanhoMAX];
    colunas = new int[tamanhoMAX];
    valores = new int[tamanhoMAX];
}

MatrizCOO::~MatrizCOO() {
    delete[] linhas;
    delete[] colunas;
    delete[] valores;
}

void MatrizCOO::Cresce() {
    int novo = 2 * tamanhoMAX;
    int* nl = new int[novo];
    int* nc = new int[novo];
    int* nv = new int[novo];

    for (int p = 0; p < tamanho; p++) {
        nl[p] = linhas[p];
        nc[p] = colunas[p];
        nv[p] = valores[p];
    }

    delete[] linhas;
    delete[] colunas;
    delete[] valores;

    linhas = nl;
    colunas = nc;
    valores = nv;
    tamanhoMAX = novo;
}

void MatrizCOO::insereElemento(int i, int j, int v) {
    if (tamanho == tamanhoMAX) { Cresce(); }
    
    int p = tamanho;
    while (p > 0 && (linhas[p-1] > i || (linhas[p-1] == i && colunas[p-1] > j))) {
        linhas[p] = linhas[p-1];
        colunas[p] = colunas[p-1];
        valores[p] = valores[p-1];
        p--;
    }

    linhas[p] = i;
    colunas[p] = j;
    valores[p] = v;
    tamanho++;
}

void MatrizCOO::removeElemento(int p) {
    for (int q = p; q < tamanho - 1; q++) {
        linhas[q] = linhas[q+1]; colunas[q] = colunas[q+1];
        valores[q] = valores[q+1];
    }
    tamanho--;
}

int MatrizCOO::BuscaBinariaGet(int i, int j) const{
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (linhas[meio] == i && colunas[meio] == j) return meio;

        if (linhas[meio] < i || (linhas[meio] == i && colunas[meio] < j)) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

int MatrizCOO::BuscaBinariaLinha(int i) const{
    int inicio = 0;
    int fim = tamanho - 1;
    int pos = tamanho;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (linhas[meio] >= i) {
            pos = meio;
            fim = meio - 1;
        } else inicio = meio + 1;
    }

    return pos;
}

int MatrizCOO::Get(int i, int j) const {
    if (i < 0 || i >= l || j < 0 || j >= c) throw "Posicao invalida";
    
    int pos = BuscaBinariaGet(i, j);
    if (pos != -1) return valores[pos];

    return 0;
}

void MatrizCOO::Set(int i, int j, int v) {
    if (i < 0 || i >= l || j < 0 || j >= c) throw "Posicao invalida";
    
    for (int p = 0; p < tamanho; p++) {
        if (linhas[p] == i && colunas[p] == j) {
            if (v == 0) removeElemento(p);
            else valores[p] = v; 
            return;
        }
    }

    if (v != 0) insereElemento(i, j, v);
}

void MatrizCOO::redimencionarMatriz(int l, int c) {
    if (l > this->l) this->l = l;
    if (c > this->c) this->c = c;
}

int MatrizCOO::somarLinha(int i) const {
    if (i < 0 || i >= l) throw "Posicao invalida";

    int soma = 0;
    int pos = BuscaBinariaLinha(i);

    while (pos < tamanho && linhas[pos] == i) {
        soma += valores[pos];
        pos++;
    }

    return soma;
}