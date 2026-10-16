#ifndef CATALOGO_H
#define CATALOGO_H

#include <string>
#include "Item.h"
#include "Atributo.h"
#include "Lista.h"
#include "Matrizes.h"

enum ModoMatriz { MODO_L, MODO_T };

class Catalogo {
private:
    ModoMatriz modo_atual;
    
    Lista<Item> itens;
    Lista<Atributo> atributos;
    Matriz* matriz_mods;

    void converterParaMatrizL();
    void converterParaMatrizT();
    void limparMatrizL();
    void limparMatrizT();

public:
    Catalogo();
    ~Catalogo();

    void definirModo(char modo); // 'L', 'T' ou C
    char getModo() const;

    void registrarItem();
    void registrarAtributo();

    void definirModificador(int id_item, int id_atributo, int valor);
    int obterModificador(int id_item, int id_atributo) const;

    int getNumItens() const;
    int getNumAtributos() const;

    int calcularPoder(int id_item) const;
    double calcularEquilibrio(int id_item) const;
    double calcularSinergia(int id_item, const int* vetor_build) const;
};

#endif