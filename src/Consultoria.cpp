#include "Consultoria.h"
#include <iostream>
#include <iomanip>

Consultoria::Consultoria() : indice(), mapa(), fila(), conectividade() {}
Consultoria::Consultoria(char modo) : indice(modo), mapa(), fila(), conectividade() {}
Consultoria::~Consultoria() {}

// E <modo> : Muda a estrutura do indice
void Consultoria::alterarModo(char modo) {
    indice.definirModo(modo); 
    std::cout << "E " << indice.getModo() << "\n";
}

// A <nome> : Cadastra um novo Atributo
void Consultoria::cadastrarAtributo(const std::string& nome) {
    int id_atributo = indice.registrarAtributo(nome);
    std::cout << "A " << id_atributo << "\n";
}

// C <nome> <k> <id_attr_1> <val_1> ... : Cadastra um novo Cliente e insere no índice
void Consultoria::cadastrarCliente(const std::string& nome, int k, const int* ids_atributos, const int* valores) {
    int num_atributos = indice.getNumAtributos();
    int* build = new int[num_atributos]();

    for (int i = 0; i < k; i++) {
        build[ids_atributos[i]] = valores[i];
    }

    int poder = 0;
    for (int i = 0; i < num_atributos; i++) {
        poder += build[i];
    }

    int id_cliente = clientes.getTamanho();
    Cliente novo_cliente(id_cliente, nome, poder);
    clientes.insereFinal(novo_cliente);

    indice.insere(novo_cliente.poder, id_cliente);

    delete[] build;

    std::cout << "C " << id_cliente << " " << novo_cliente.poder << "\n";
}

// D <id_cliente> : Encerra atendimento do cliente e o remove do índice
void Consultoria::encerrarCliente(int id_cliente) {
    const Cliente& c = clientes.getRegistro(id_cliente);
    indice.remove(c.poder, id_cliente);

    std::cout << "D " << c.nome << " " << c.poder << "\n";
}

// BP <poder> : Busca clientes ativos com poder exato e mostra em ordem crescente de id
void Consultoria::buscarPorPoder(int poder) const {
    Lista<int> ids_encontrados;
    indice.buscaPontual(poder, ids_encontrados);

    std::cout << "BP " << poder;

    if (ids_encontrados.vazia()) { std::cout << " VAZIO\n"; }

    else {
        for (int i = 0; i < ids_encontrados.getTamanho(); i++) {
            std::cout << " cliente_" << (i + 1) << " " << ids_encontrados.getRegistro(i);
        }
        std::cout << "\n";
    }
}

// BF <min> <max> : Busca clientes ativos na faixa e mostra em ordem crescente de poder (desempate por id)
void Consultoria::buscarPorFaixa(int min, int max) const {
    Lista<DadoIndice> regs_encontrados;
    indice.buscaFaixa(min, max, regs_encontrados);

    std::cout << "BF " << min << " " << max;

    if (regs_encontrados.vazia()) { std::cout << " VAZIO\n"; }

    else {
        for (int i = 0; i < regs_encontrados.getTamanho(); i++) {
            std::cout << " cliente_" << (i + 1) << " " 
                      << regs_encontrados.getRegistro(i).id_cliente << " " 
                      << regs_encontrados.getRegistro(i).poder;
        }
        std::cout << "\n";
    }
}

// R <nome> : Cadastra uma nova região no Mapa e nos Conjuntos Disjuntos
void Consultoria::cadastrarRegiao(const std::string& nome) {
    int id_regiao = mapa.adicionarRegiao(nome);
    conectividade.Make(id_regiao);

    std::cout << "R " << id_regiao << "\n";
}

// T <id_regiao_1> <id_regiao_2> <custo> : Cria rota de mão dupla e une os conjuntos
void Consultoria::cadastrarRota(int id_regiao_1, int id_regiao_2, int custo) {
    mapa.adicionarRota(id_regiao_1, id_regiao_2, custo);
    conectividade.Union(id_regiao_1, id_regiao_2);

    std::cout << "T " 
              << mapa.getNomeRegiao(id_regiao_1) << " "
              << mapa.getNomeRegiao(id_regiao_2) << " " 
              << custo << "\n";
}

// CC <id_regiao_1> <id_regiao_2> : Verifica se há caminho entre as regiões
void Consultoria::consultarCaminho(int id_regiao_1, int id_regiao_2) {
    bool conectados = (conectividade.Find(id_regiao_1) == conectividade.Find(id_regiao_2));

    std::cout << "CC " 
              << mapa.getNomeRegiao(id_regiao_1) << " "
              << mapa.getNomeRegiao(id_regiao_2) << " "
              << (conectados ? "SIM" : "NAO") << "\n";
}

// F <id_cliente> <prioridade> : Insere cliente na fila de prioridade da consultoria
void Consultoria::inserirFila(int id_cliente, int prioridade) {
    fila.Insere(id_cliente, prioridade);
    std::cout << "F " << fila.getTamanho() << "\n";
}

// Z <k> : Atende até k clientes de maior prioridade (desempate pelo menor ID)
void Consultoria::atenderClientes(int k) {
    int* ids_atendidos = new int[k];
    int* prioridades_atendidas = new int[k];
    int n_atendidos = 0;

    while (n_atendidos < k && !fila.Vazia()) {
        NoHeap cliente = fila.Remove();
        ids_atendidos[n_atendidos] = cliente.id_cliente;
        prioridades_atendidas[n_atendidos] = cliente.prioridade;
        n_atendidos++;
    }

    std::cout << "Z " << n_atendidos << "\n";
    if (n_atendidos > 0) {
        for (int i = 0; i < n_atendidos; i++) {
            std::cout << "atendimento_" << (i + 1) << " "
                      << ids_atendidos[i] << " " 
                      << prioridades_atendidas[i];

            if (i < n_atendidos - 1) std::cout << " ";
        }
        std::cout << "\n";
    }

    delete[] ids_atendidos;
    delete[] prioridades_atendidas;
}