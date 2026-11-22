#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

// Elemento armazenado no Heap (chave composta: prioridade + id_cliente)
struct NoHeap {
    int id_cliente;
    int prioridade;
};

class FilaPrioridade {
private:
    NoHeap* v; 
    int tamanho;
    int capacidade;

    static const int TAMANHO_INICIAL = 16;

    int GetAncestral(int i) const { return (i - 1) / 2; }
    int GetSucessorEsq(int i) const { return 2 * i + 1; }
    int GetSucessorDir(int i) const { return 2 * i + 2; }

    void Sobe(int i);
    void Desce(int i);
    void Redimensionar();

    bool vemAntes(const NoHeap& a, const NoHeap& b) const;

public:
    FilaPrioridade(int capacidade = TAMANHO_INICIAL);
    ~FilaPrioridade();

    // Insere cliente com sua prioridade
    void Insere(int id_cliente, int prioridade);
    
    // Remove e retorna o cliente de maior prioridade
    NoHeap Remove();

    // Consulta o cliente de maior prioridade
    NoHeap Maximo() const;

    // Funções utilitarias
    int getTamanho() const { return tamanho; }
    bool Vazia() const { return tamanho == 0; }
};

#endif