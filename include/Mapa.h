#ifndef MAPA_H
#define MAPA_H

#include <string>

// Nó da lista de adjacência
struct Aresta {
    int destino;
    int custo;
    Aresta* prox;

    Aresta(int destino, int custo, Aresta* prox = nullptr): destino(destino), custo(custo), prox(prox) {}
};

class Mapa {
private:
    std::string* rotulos;   // Rótulo textual de cada vértice
    Aresta** listas;        // Vetor de listas de adjacência
    // Aresta* pitervertice;

    int capacidade;
    int num_vertices;
    int num_arestas;

    static const int CAPACIDADE_INICIAL = 16;

    // Dobra a capacidade dos vetores dinâmicos quando novas regiões são cadastradas
    void redimensionar();

public:
    Mapa(int capacidade_inicial = CAPACIDADE_INICIAL);
    ~Mapa();

    // Cadastra uma nova região e retorna seu id atribuido
    int adicionarRegiao(const std::string& nome);

    // Insere rota de mão dupla
    void adicionarRota(int origem, int destino, int custo);

    // Consultas de vértices e rótulos
    int getNumRotas() const { return num_arestas; }
    int getNumRegioes() const { return num_vertices; }
    int getIdRegiao(const std::string& nome) const;
    std::string getNomeRegiao(int id) const;
    const Aresta* getVizinhos(int id_regiao) const;

    // // Passo 4 da Análise Experimental: verifica conectividade percorrendo o mapa (BFS/DFS)
    // // Retorna true se alcançável e registra o número de regiões visitadas na consulta
    // bool existeCaminhoBusca(int origem, int destino, int& regioes_visitadas) const;
};

#endif