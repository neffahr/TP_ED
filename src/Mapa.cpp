#include "Mapa.h"
#include <stdexcept>
#include <climits>

Mapa::Mapa(int capacidade_inicial) {
    capacidade = (capacidade_inicial > 0) ? capacidade_inicial : CAPACIDADE_INICIAL;
    num_vertices = 0;
    num_arestas = 0;

    rotulos = new std::string[capacidade];
    listas = new Aresta*[capacidade];

    for (int i = 0; i < capacidade; i++) {
        listas[i] = nullptr;
    }
}

Mapa::~Mapa() {
    for (int i = 0; i < num_vertices; i++) {
        Aresta* atual = listas[i];
        while (atual != nullptr) {
            Aresta* prox = atual->prox;
            delete atual;
            atual = prox;
        }
    }

    delete[] listas;
    delete[] rotulos;
}

void Mapa::redimensionar() {
    int nova_capacidade = capacidade * 2;
    std::string* novos_rotulos = new std::string[nova_capacidade];
    Aresta** nova_listas = new Aresta*[nova_capacidade];

    for (int i = 0; i < num_vertices; i++) {
        novos_rotulos[i] = rotulos[i];
        nova_listas[i] = listas[i];
    }
    for (int i = num_vertices; i < nova_capacidade; i++) {
        nova_listas[i] = nullptr;
    }

    delete[] rotulos;
    delete[] listas;

    rotulos = novos_rotulos;
    listas = nova_listas;
    capacidade = nova_capacidade;
}


int Mapa::adicionarRegiao(const std::string& nome) {
    if (num_vertices == capacidade) redimensionar();

    int id = num_vertices;
    rotulos[id] = nome;
    listas[id] = nullptr;
    num_vertices++;

    return id;
}

void Mapa::adicionarRota(int origem, int destino, int custo) {
    if (origem < 0 || origem >= num_vertices || destino < 0 || destino >= num_vertices) {
        throw std::out_of_range("ERRO: Regiao invalida ao inserir rota!");
    }

    listas[origem] = new Aresta(destino, custo, listas[origem]); // Insere elemento de aresta no início da lista
    if (origem != destino) {
        listas[destino] = new Aresta(origem, custo, listas[destino]);
    }
    num_arestas++;
}


std::string Mapa::getNomeRegiao(int id) const {
    if (id < 0 || id >= num_vertices) throw std::out_of_range("ERRO: ID de regiao invalido!");
    return rotulos[id];
}

int Mapa::getIdRegiao(const std::string& nome) const {
    for (int i = 0; i < num_vertices; i++) {
        if (rotulos[i] == nome) {
            return i;
        }
    }
    return -1;
}

const Aresta* Mapa::getVizinhos(int id_regiao) const {
    if (id_regiao < 0 || id_regiao >= num_vertices) throw std::out_of_range("ERRO: ID de regiao invalido!");
    return listas[id_regiao];
}