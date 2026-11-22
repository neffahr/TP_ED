#ifndef INDICE_H
#define INDICE_H

#include <string>
#include "Cliente.h"
#include "Lista.h"
#include "ArvoreAVL.h"
#include "Hash.h"

enum ModoIndice { MODO_A, MODO_H };

class Indice {
private:
    ModoIndice modo_atual;

    Lista<Atributo> atributos;
    

    void converterParaMatrizL();
    void converterParaMatrizT();

    int pesquisaBinaria(int valor_mod) const;

public:
    Indice();
    Indice(char modo);
    ~Indice();

    void definirModo(char modo); // 'L' ou 'T'
    char getModo() const;
    
    std::string getNomeItem(int id_item) const;
    std::string getNomeAtributo(int id_atributo) const;
    int getNumItens() const;
    int getNumAtributos() const;

    int registrarItem(const std::string& nome);
    int registrarAtributo(const std::string& nome);

    void definirModificador(int id_item, int id_atributo, int valor);
    int obterModificador(int id_item, int id_atributo) const;

    int getAtributosDoItem(int id_item, int*& ids_atributos, int*& valores);
    int getItensDoAtributo(int id_atributo, int*& ids_itens, int*& valores);
    
    int calcularPoder(int id_item) const;
    double calcularEquilibrio(int id_item) const;
    double calcularSinergia(int id_item, const double* vetor_build, int soma_vetor_build) const;
};

#endif