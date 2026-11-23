#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include "EstruturaIndice.h"
#include "Lista.h"

struct NoAVL {
    DadoIndice registro;

    int altura; // Altura do nó
    NoAVL* esq;
    NoAVL* dir;

    NoAVL(int poder, int id_cliente): registro(DadoIndice(poder, id_cliente)), altura(0), esq(nullptr), dir(nullptr) {}
};

class ArvoreAVL : public EstruturaIndice {
private:
    NoAVL* raiz;

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
    void buscaFaixaRec(NoAVL* p, int min, int max, Lista<DadoIndice>& resultado) const;
    void emOrdemRec(NoAVL* p, Lista<DadoIndice>& registros) const;

public:
    ArvoreAVL();
    ~ArvoreAVL() override;

    void insere(int poder, int id_cliente) override;
    void remove(int poder, int id_cliente) override;

    // Responde BP <poder> em ordem crescente de id
    void buscaPontual(int poder, Lista<int>& resultado) const override;

    // Responde BF <min> <max> em ordem crescente de poder e depois id
    void buscaFaixa(int min, int max, Lista<DadoIndice>& resultado) const override;

    // Extrai todos os elementos em ordem para migração de modo
    void exportarElementos(Lista<DadoIndice>& resultado) const override;

    int getTamanho() const override;
    bool vazia() const override;
};

#endif