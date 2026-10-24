#ifndef FORJA_H
#define FORJA_H

#include <string>
#include "Aventureiro.h"
#include "Catalogo.h"
#include "Fila.h"
#include "Lista.h"

class Forja {
private:
    Catalogo catalogo;          
    Fila fila_encomendas;     
    Lista<Aventureiro> aventureiros;

    // Usa catalogo e aventureiro da lista para calcular o vetor de build
    void calcularVetorBuild(int id_aventureiro, double* vetor_build);
    // Algoritmo de ordenação (MergeSort/QuickSort)
    static void ordenar(int* ids_itens, double *valores, int n);

public:
    Forja();
    Forja(char modo);
    ~Forja();

    // E <modo> : Altera a representação da matriz do catálogo ('L' ou 'T')
    void alterarModo(char modo);

    // A <nome> : Cadastra um novo Atributo
    void cadastrarAtributo(const std::string& nome);

    // I <nome> : Cadastra um novo Item
    void cadastrarItem(const std::string& nome);

    // M <id_item> <id_atributo> <valor> : Define ou modifica um modificador no catálogo
    void definirModificador(int id_item, int id_atributo, int valor);

    // H <nome> : Cadastra um novo Aventureiro
    void cadastrarAventureiro(const std::string& nome);

    // F <id_aventureiro> <id_item> : Registra encomenda ao final da fila global
    void adicionarEncomenda(int id_aventureiro, int id_item);

    // Z <k> : Executa k turnos de trabalho (forja encomenda do início da fila e equipa no aventureiro)
    void trabalharTurnos(int k);

    // D <id_aventureiro> : Desequipa a última peça equipada da build do aventureiro
    void desequiparPecaAventureiro(int id_aventureiro);

    // LI <id_item> : Lista todos os modificadores de um item
    void consultarItem(int id_item);

    // LA <id_atributo> : Lista todos os itens com modificadores não-nulos para um determinado atributo
    void consultarAtributo(int id_atributo);

    // LH <id_aventureiro> : Lista vetor de build de cada atributo do aventureiro
    void consultarBuild(int id_aventureiro);

    // Q <id_aventureiro> <n> <m> <M_1> <w_1> ... <M_m> <w_m> : Consulta de recomendação de itens
    void consultarRecomendacao(int id_aventureiro, int n_recomendacoes, int m_metricas, 
                  const std::string* nomes_metricas, const double* pesos_metricas);
};

#endif