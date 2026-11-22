#ifndef CONSULTORIA_H
#define CONSULTORIA_H

#include <string>
#include "Atributo.h"
#include "Cliente.h"
#include "Indice.h"
#include "Mapa.h"
#include "FilaPrioridade.h"
#include "ConjuntosDisjuntos.h"
#include "Lista.h"

class Consultoria {
private:
    Lista<Cliente> clientes;
    Indice indice;
    FilaPrioridade fila;
    Mapa mapa;
    ConjuntosDisjuntos conectividade;

public:
    Consultoria();
    Consultoria(char modo);
    ~Consultoria();

    // E <modo> : Altera a representação do índice ('A' para AVL ou 'H' para Hash)
    void alterarModo(char modo);

    // A <nome> : Cadastra um novo Atributo
    void cadastrarAtributo(const std::string& nome);

    // C <nome> <k> <id_attr_1> <val_1> ... : Cadastra um novo Cliente e insere no índice
    void cadastrarCliente(const std::string& nome, int k, const int* ids_atributos, const int* valores);

    // D <id_cliente> : Encerra atendimento do cliente e o remove do índice
    void encerrarCliente(int id_cliente);

    // BP <poder> : Busca clientes ativos com poder exato (ordem crescente de ID)
    void buscarPorPoder(int poder) const;

    // BF <min> <max> : Busca clientes ativos na faixa (ordem crescente de poder, desempate por ID)
    void buscarPorFaixa(int min, int max) const;

    // R <nome> : Cadastra uma nova região no Mapa e nos Conjuntos Disjuntos
    void cadastrarRegiao(const std::string& nome);

    // T <id_regiao_1> <id_regiao_2> <custo> : Cria rota de mão dupla e une os conjuntos
    void cadastrarRota(int id_regiao_1, int id_regiao_2, int custo);

    // CC <id_regiao_1> <id_regiao_2> : Verifica se há caminho entre as regiões
    void consultarCaminho(int id_regiao_1, int id_regiao_2);

    // F <id_cliente> <prioridade> : Insere cliente na fila de prioridade da consultoria
    void inserirFila(int id_cliente, int prioridade);

    // Z <k> : Atende até k clientes de maior prioridade (desempate pelo menor ID)
    void atenderClientes(int k);
};

#endif