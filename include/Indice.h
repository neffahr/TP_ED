#ifndef INDICE_HPP
#define INDICE_HPP

#include <string>
#include "Atributo.h"
#include "Lista.h"
#include "EstruturaIndice.h"
#include "ArvoreAVL.h"
#include "Hash.h"

enum ModoIndice { MODO_A, MODO_H };

class Indice {
private:
    ModoIndice modo;
    Lista<Atributo> atributos;
    EstruturaIndice* indice;

    void converterParaAVL();
    void converterParaHash();

public:
    Indice(char modo = 'A');
    ~Indice();

    void definirModo(char modo);

    // Cadastro de Atributos
    int registrarAtributo(const std::string& nome);

    // Operações sobre o indice
    void insere(int poder, int id_cliente);
    void remove(int poder, int id_cliente);

    void buscaPontual(int poder, Lista<int>& resultado) const;
    void buscaFaixa(int min, int max, Lista<DadoIndice>& resultado) const;

    // Métodos Auxiliares
    char getModo() const;
    int getNumAtributos() const;
    std::string getNomeAtributo(int id_atributo) const;
    int getTamanho() const;
    bool vazia() const;
};

#endif