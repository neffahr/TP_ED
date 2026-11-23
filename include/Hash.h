#ifndef HASH_HPP
#define HASH_HPP

#include "EstruturaIndice.h"
#include "Lista.h"

// Célula da lista encadeada
struct NoHash {
    DadoIndice registro;
    NoHash* prox;

    NoHash(int poder, int id_cliente, NoHash* prox = nullptr): registro(DadoIndice(poder, id_cliente)), prox(prox) {}
};

class Hash : public EstruturaIndice {
private:
    NoHash** tabela;    // Vetor de M listas encadeadas
    int M;              // Número de listas

    static const int M_INICIAL = 101;

    int funcaoHash(int chave) const { return ((chave % M) + M) % M; }

    // Auxiliares
    bool ehPrimo(int n) const;
    int proximoPrimo(int n) const;
    void rehash();
    void limpa();

public:
    Hash(int tamanho_inicial = M_INICIAL);
    ~Hash() override;

    void insere(int poder, int id_cliente) override;
    void remove(int poder, int id_cliente) override;

    // Responde BP <poder>: busca no escaninho e ordena por id
    void buscaPontual(int poder, Lista<int>& resultado) const override;

    // Responde BF <min> <max>: varre os M escaninhos e ordena por poder (desempate por id)
    void buscaFaixa(int min, int max, Lista<DadoIndice>& resultado) const override;

    // Extrai todos os elementos ativos para migração de modo
    void exportarElementos(Lista<DadoIndice>& registros) const override;

    int getTamanho() const override { return tamanho; }
    bool vazia() const override { return tamanho == 0; }
};

#endif