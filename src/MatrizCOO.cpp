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

void MatrizCOO::InsereElemento(int i, int j, int v) {
    if (tamanho == tamanhoMAX) {
        Cresce();
    }
    
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

int MatrizCOO::Get(int i, int j) const {
    if (i < 0 || i >= l || j < 0 || j >= c) {
        throw "Posicao invalida";
    }
    
    for (int p = 0; p < tamanho; p++) {
        if (linhas[p] == i && colunas[p] == j) {
            return valores[p];
        }
    }
    
    return 0;
}

void MatrizCOO::Set(int i, int j, int v) {
    if (i < 0 || i >= l || j < 0 || j >= c) {
        throw "Posicao invalida";
    }
    
    for (int p = 0; p < tamanho; p++) {
        if (linhas[p] == i && colunas[p] == j) {
            if (v == 0) {
                RemoveElemento(p);
            } else {
                valores[p] = v; 
            }
            return;
        }
    }

    // Se não encontrou no laço e o valor for diferente de 0, aloca-o em ordem
    if (v != 0.0) {
        InsereElemento(i, j, v);
    }
}

void MatrizEncadeada::redimencionarMatriz(int l, int c) {

}

int MatrizEncadeada::somarLinha(int i) const {
    
}