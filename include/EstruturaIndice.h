#ifndef ESTRUTURA_INDICE_H
#define ESTRUTURA_INDICE_H

#include "Lista.h"

struct DadoIndice {
    int poder;          // Chave primária de ordenação
    int id_cliente;     // Chave de desempate

    DadoIndice() : poder(0), id_cliente(-1) {}
    DadoIndice(int poder, int id_cliente) : poder(poder), id_cliente(id_cliente) {}

    bool operator<(const DadoIndice& outro) const {
        if (poder != outro.poder) return poder < outro.poder;
        return id_cliente < outro.id_cliente;
    }

    bool operator>(const DadoIndice& outro) const {
        if (poder != outro.poder) return poder > outro.poder;
        return id_cliente > outro.id_cliente;
    }

    bool operator==(const DadoIndice& outro) const {
        return poder == outro.poder && id_cliente == outro.id_cliente;
    }
};

class EstruturaIndice {
protected:
    int tamanho;

public:
    EstruturaIndice() {}
    virtual ~EstruturaIndice() {}

    virtual void insere(int poder, int id_cliente) = 0;
    virtual void remove(int poder, int id_cliente) = 0;

    // Responde BP <poder>
    virtual void buscaPontual(int poder, Lista<int>& resultado) const = 0;

    // Responde BF <min> <max>
    virtual void buscaFaixa(int min, int max, Lista<DadoIndice>& resultado) const = 0;

    // Extrai todos os elementos para migração de modo
    virtual void exportarElementos(Lista<DadoIndice>& registros) const = 0;

    virtual int getTamanho() const = 0;
    virtual bool vazia() const = 0;
};

#endif