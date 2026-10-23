#ifndef CATALOGO_H
#define CATALOGO_H

#include <string>
#include "Item.h"
#include "Atributo.h"
#include "Lista.h"
#include "Matriz.h"
#include "MatrizCOO.h"
#include "MatrizEncadeada.h"

enum ModoMatriz { MODO_L, MODO_T };

class Catalogo {
private:
    ModoMatriz modo_atual;
    
    Lista<Item> itens;
    Lista<Atributo> atributos;
    Matriz* matriz_mods;

    void converterParaMatrizL();
    void converterParaMatrizT();
    
    double calcularPontuacaoItem(
        int id_item, int id_aventureiro, 
        int m_metricas, const std::string* nomes_metricas, 
        const double* pesos_metricas
    ) const;

    int pesquisaBinaria(int valor_mod) const;

public:
    Catalogo();
    ~Catalogo();

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