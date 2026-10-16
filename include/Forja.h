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

    void redimensionarAventureiros();

    double calcularPontuacaoItem(int id_item, int id_aventureiro, 
                                 int m_metricas, const std::string* nomes_metricas, 
                                 const double* pesos_metricas) const;

    // Algoritmo de ordenação (MergeSort/QuickSort interno)
    void ordenarRecomendacoes(int* ids_itens, double* pontuacoes, int n) const;

public:
    Forja();
    ~Forja();

    // --- Processador de Entrada ---
    bool processarComando(const std::string& linha);

    // E <modo> : Altera a representação da matriz do catálogo ('L', 'T' ou 'C')
    void alterarModo(char modo);

    // A <nome> : Cadastra um novo Atributo
    void cadastrarAtributo(const std::string& nome);

    // I <nome> : Cadastra um novo Item
    void cadastrarItem(const std::string& nome);

    // M <id_item> <id_atributo> <valor> : Define ou modifica um modificador no catálogo
    void difinirModificador(int id_item, int id_atributo, int valor);

    // H <nome> : Cadastra um novo Aventureiro
    void cadastrarAventureiro(const std::string& nome);

    // F <id_aventureiro> <id_item> : Registra encomenda ao final da fila global
    void adicionarEncomenda(int id_aventureiro, int id_item);

    // Z <k> : Executa k turnos de trabalho (forja encomenda do início da fila e equipa no aventureiro)
    void trabalharTurnos(int k);

    // D <id_aventureiro> : Desequipa a última peça equipada da build do aventureiro
    void desequiparPecaAventureiro(int id_aventureiro);

    // LI <id_item> : Lista todos os modificadores de um item
    void consultarItem(int id_item) const;

    // LA <id_atributo> : Lista todos os itens com modificadores não-nulos para um determinado atributo
    void consultarAtributo(int id_atributo) const;

    // LH <id_aventureiro> : Lista vetor de build de cada atributo do aventureiro
    void consultarBuild(int id_aventureiro) const;

    // Q <id_aventureiro> <n> <m> <M_1> <w_1> ... <M_m> <w_m> : Consulta de recomendação de itens
    void consultarRecomendacao(int id_aventureiro, int n_recomendacoes, int m_metricas, 
                  const std::string* nomes_metricas, const double* pesos_metricas) const;

    // --- Funcionalidades de Pontos Extras ---

    // LF <id_atributo> <valor_min> <valor_max> : Consulta de itens por faixa de valores
    void consultarItensNaFaixa(int id_atributo, int valor_min, int valor_max) const;

    // --- Consultores e Métricas para Análise Experimental e Testes ---
    // int getNumAventureiros() const;
    // int getTamanhoFila() const;
    // char getModoMatriz() const;
};

#endif