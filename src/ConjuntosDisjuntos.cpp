#include "ConjuntosDisjuntos.h"
#include <stdexcept>

ConjuntosDisjuntos::ConjuntosDisjuntos(int capacidade_inicial) {
    capacidade = (capacidade_inicial > 0) ? capacidade_inicial : CAPACIDADE_INICIAL;
    tamanho = 0;
    num_conjuntos = 0;

    pai = new int[capacidade];
    rank = new int[capacidade];

    for (int i = 0; i < capacidade; i++) {
        pai[i] = -1;
        rank[i] = 0;
    }
}

ConjuntosDisjuntos::~ConjuntosDisjuntos() {
    delete[] pai;
    delete[] rank;
}


void ConjuntosDisjuntos::redimensionar(int nova_capacidade) {
    int* novo_pai = new int[nova_capacidade];
    int* novo_rank = new int[nova_capacidade];

    for (int i = 0; i < tamanho; i++) {
        novo_pai[i] = pai[i];
        novo_rank[i] = rank[i];
    }
    for (int i = tamanho; i < nova_capacidade; i++) {
        novo_pai[i] = -1;
        novo_rank[i] = 0;
    }

    delete[] pai;
    delete[] rank;

    pai = novo_pai;
    rank = novo_rank;
    capacidade = nova_capacidade;
}


void ConjuntosDisjuntos::Make(int x) {
    if (x >= capacidade) {
        int nova_cap = capacidade;
        while (nova_cap <= x) {
            nova_cap *= 2;
        }
        redimensionar(nova_cap);
    }

    if (pai[x] == -1) {
        pai[x] = x;
        rank[x] = 0;
        num_conjuntos++;
        if (x >= tamanho) {
            tamanho = x + 1;
        }
    }
}

int ConjuntosDisjuntos::Find(int x) {
    if (pai[x] != x) {
        pai[x] = Find(pai[x]);
    }
    return pai[x];
}

void ConjuntosDisjuntos::Union(int x, int y) {
    int rx = Find(x);
    int ry = Find(y);

    if (rx == ry) {
        return;
    }

    if (rank[rx] < rank[ry]) {
        pai[rx] = ry;
    } else if (rank[rx] > rank[ry]) {
        pai[ry] = rx;
    } else {
        pai[ry] = rx;
        rank[rx]++;
    }

    num_conjuntos--;
}

bool ConjuntosDisjuntos::conectados(int x, int y) {
    return Find(x) == Find(y);
}