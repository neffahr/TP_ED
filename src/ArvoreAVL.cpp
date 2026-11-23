#include "ArvoreAVL.h"

ArvoreAVL::ArvoreAVL() {
    raiz = nullptr;
}

static void limpaRec(NoAVL* p) {
    if (p == nullptr) return;
    limpaRec(p->esq);
    limpaRec(p->dir);
    delete p;
}

ArvoreAVL::~ArvoreAVL() {
    limpaRec(raiz);
    raiz = nullptr;
}


int ArvoreAVL::altura(NoAVL* p) const {
    return (p == nullptr) ? -1 : p->altura;
}

int ArvoreAVL::FB(NoAVL* p) const {
    if (p == nullptr) return 0;
    return altura(p->dir) - altura(p->esq);
}

void ArvoreAVL::atualizaAltura(NoAVL* p) {
    if (p == nullptr) return;
    int h_esq = altura(p->esq);
    int h_dir = altura(p->dir);
    p->altura = ((h_esq > h_dir) ? h_esq : h_dir) + 1;
}


NoAVL* ArvoreAVL::rotacaoDireita(NoAVL* x) {
    NoAVL* f = x->esq;      // f vai subir
    x->esq = f->dir;        // subárvore do meio troca de pai
    f->dir = x;             // x desce para a direita

    atualizaAltura(x);      // atualiza quem desceu primeiro
    atualizaAltura(f);      // depois quem subiu
    return f;               // nova raiz da subárvore
}

NoAVL* ArvoreAVL::rotacaoEsquerda(NoAVL* x) {
    NoAVL* f = x->dir;      // f vai subir
    x->dir = f->esq;        // subárvore do meio troca de pai
    f->esq = x;             // x desce para a esquerda

    atualizaAltura(x);      // atualiza quem desceu primeiro
    atualizaAltura(f);      // depois quem subiu
    return f;               // nova raiz da subárvore
}

NoAVL* ArvoreAVL::balancear(NoAVL* p) {
    atualizaAltura(p);
    int fb = FB(p);

    if (fb == -2) {                         // pesa à esquerda
        if (FB(p->esq) > 0)                 // sinais trocados: caso ED (dupla)
            p->esq = rotacaoEsquerda(p->esq);
        return rotacaoDireita(p);           // caso EE ou segundo passo de ED
    } 
    else if (fb == 2) {                     // pesa à direita
        if (FB(p->dir) < 0)                 // sinais trocados: caso DE (dupla)
            p->dir = rotacaoDireita(p->dir);
        return rotacaoEsquerda(p);          // caso DD ou segundo passo de DE
    }

    return p;
}


NoAVL* ArvoreAVL::insereRec(NoAVL* p, int poder, int id_cliente) {
    if (p == nullptr) {
        return new NoAVL(poder, id_cliente);
    }

    DadoIndice novo(poder, id_cliente);

    if (novo < p->registro) {
        p->esq = insereRec(p->esq, poder, id_cliente);
    } else if (novo > p->registro) {
        p->dir = insereRec(p->dir, poder, id_cliente);
    } else {
        return p;
    }

    return balancear(p);
}

void ArvoreAVL::insere(int poder, int id_cliente) {
    raiz = insereRec(raiz, poder, id_cliente);
}

NoAVL* ArvoreAVL::menorNo(NoAVL* p) const {
    NoAVL* atual = p;
    while (atual != nullptr && atual->esq != nullptr) {
        atual = atual->esq;
    }
    return atual;
}

NoAVL* ArvoreAVL::removeRec(NoAVL* p, int poder, int id_cliente) {
    if (p == nullptr) { return nullptr; }

    DadoIndice alvo(poder, id_cliente);

    if (alvo < p->registro) {
        p->esq = removeRec(p->esq, poder, id_cliente);
    } else if (alvo > p->registro) {
        p->dir = removeRec(p->dir, poder, id_cliente);
    } else {
        if (p->esq == nullptr || p->dir == nullptr) {
            NoAVL* filho = (p->esq != nullptr) ? p->esq : p->dir;
            delete p;
            return filho;
        } else {
            NoAVL* sucessor = menorNo(p->dir);
            p->registro = sucessor->registro;
            p->dir = removeRec(p->dir, sucessor->registro.poder, sucessor->registro.id_cliente);
        }
    }

    return balancear(p);
}

void ArvoreAVL::remove(int poder, int id_cliente) {
    raiz = removeRec(raiz, poder, id_cliente);
}


void ArvoreAVL::buscaPontualRec(NoAVL* p, int poder, Lista<int>& resultado) const {
    if (p == nullptr) return;

    if (p->registro.poder >= poder) 
        buscaPontualRec(p->esq, poder, resultado);

    if (p->registro.poder == poder)
        resultado.insereFinal(p->registro.id_cliente);

    if (p->registro.poder <= poder)
        buscaPontualRec(p->dir, poder, resultado);
}

void ArvoreAVL::buscaPontual(int poder, Lista<int>& resultado) const {
    buscaPontualRec(raiz, poder, resultado);
}

void ArvoreAVL::buscaFaixaRec(NoAVL* p, int min, int max, Lista<DadoIndice>& resultado) const {
    if (p == nullptr) return;

    if (p->registro.poder >= min)
        buscaFaixaRec(p->esq, min, max, resultado);

    if (p->registro.poder >= min && p->registro.poder <= max)
        resultado.insereFinal(p->registro);

    if (p->registro.poder <= max)
        buscaFaixaRec(p->dir, min, max, resultado);
}

void ArvoreAVL::buscaFaixa(int min, int max, Lista<DadoIndice>& resultado) const {
    if (min > max || raiz == nullptr) return;
    buscaFaixaRec(raiz, min, max, resultado);
}


void ArvoreAVL::emOrdemRec(NoAVL* p, Lista<DadoIndice>& registros) const {
    if (p == nullptr) return;
    emOrdemRec(p->esq, registros);
    registros.insereFinal(p->registro);
    emOrdemRec(p->dir, registros);
}

void ArvoreAVL::exportarElementos(Lista<DadoIndice>& registros) const {
    emOrdemRec(raiz, registros);
}


static int contaNosRec(NoAVL* p) {
    if (p == nullptr) return 0;
    return 1 + contaNosRec(p->esq) + contaNosRec(p->dir);
}

int ArvoreAVL::getTamanho() const {
    return contaNosRec(raiz);
}

bool ArvoreAVL::vazia() const {
    return raiz == nullptr;
}