#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include "Lista.h"

struct NoAVL {
    int poder;          // Chave primária de ordenação
    int id_cliente;     // Chave de desempate
    int altura;         // Altura do nó
    NoAVL* esq;
    NoAVL* dir;

    NoAVL(int poder, int id_cliente): poder(poder), id_cliente(id_cliente), altura(0), esq(nullptr), dir(nullptr) {}
};

class ArvoreAVL {
private:
    NoAVL* raiz;
    int tamanho;

    int altura(NoAVL* p) const;
    int fatorBalanceamento(NoAVL* p) const;
    void atualizaAltura(NoAVL* p);

    NoAVL* rotacaoDireita(NoAVL* x);
    NoAVL* rotacaoEsquerda(NoAVL* x);
    NoAVL* balancear(NoAVL* p);

    NoAVL* insereRec(NoAVL* p, int poder, int id_cliente);
    NoAVL* removeRec(NoAVL* p, int poder, int id_cliente);
    NoAVL* menorNo(NoAVL* p) const;

    void buscaPontualRec(NoAVL* p, int poder, Lista<int>& resultado) const;
    void buscaFaixaRec(NoAVL* p, int min, int max, Lista<int>& ids, Lista<int>& poderes) const;
    void emOrdemRec(NoAVL* p, Lista<int>& ids, Lista<int>& poderes) const;
    void limpaRec(NoAVL* p);

public:
    ArvoreAVL();
    ~ArvoreAVL();

    void insere(int poder, int id_cliente);
    void remove(int poder, int id_cliente);

    // Responde BP <poder> em ordem crescente de ID
    void buscaPontual(int poder, Lista<int>& resultado) const;

    // Responde BF <min> <max> em ordem crescente de (poder, id_cliente)
    void buscaFaixa(int min, int max, Lista<int>& ids, Lista<int>& poderes) const;

    // Extrai todos os elementos para migração de modo (A -> H)
    void exportarEmOrdem(Lista<int>& ids, Lista<int>& poderes) const;

    int getTamanho() const;
    bool vazia() const;
    void limpa();
};

#endif