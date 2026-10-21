#include "Forja.h"
#include <iostream>

Forja::Forja() {}
Forja::~Forja() {}

void Forja::alterarModo(char modo) {
    catalogo.definirModo(modo); 
}

// A <nome> : Cadastra um novo Atributo
void Forja::cadastrarAtributo(const std::string& nome) {
    int id_atributo = catalogo.registrarAtributo(nome);
    std::cout << "A " << id_atributo << "\n";
}

// I <nome> : Cadastra um novo Item
void Forja::cadastrarItem(const std::string& nome) {
    int id_item = catalogo.registrarItem(nome);
    std::cout << "I " << id_item << "\n";
}

// M <id_item> <id_atributo> <valor> : Define ou modifica um modificador
void Forja::definirModificador(int id_item, int id_atributo, int valor) {
    catalogo.definirModificador(id_item, id_atributo, valor);
    
    std::string nome_item = catalogo.getNomeItem(id_item);
    std::string nome_atributo = catalogo.getNomeAtributo(id_atributo);
    std::cout << "M " << nome_item << " " << nome_atributo << " " << valor << "\n"; 
}

// H <nome> : Cadastra um novo Aventureiro
void Forja::cadastrarAventureiro(const std::string& nome) {
    int id_novo = aventureiros.getTamanho();
    Aventureiro novo_aventureiro(id_novo, nome);
    aventureiros.insereFinal(novo_aventureiro);
    
    std::cout << "H " << id_novo << "\n";
}

// F <id_aventureiro> <id_item> : Registra encomenda ao final da fila global
void Forja::adicionarEncomenda(int id_aventureiro, int id_item) {
    fila_encomendas.enfileirar(id_aventureiro, id_item);
    
    // O tamanho da fila apos enfileirar corresponde a posicao
    int posicao = fila_encomendas.getTamanho(); 
    std::cout << "F " << posicao << "\n"; 
}

// Z <k> : Executa k turnos de trabalho
void Forja::trabalharTurnos(int k) {
    
    // Arrays ou strings temporárias para armazenar a saída das encomendas forjadas, 
    int ids_aventureiros[k];
    int ids_itens[k];
    
    int forjadas = 0;
    while (forjadas < k && !fila_encomendas.vazia()) {
        Encomenda enc = fila_encomendas.desenfileirar();
        
        ids_aventureiros[forjadas] = enc.id_aventureiro;
        ids_itens[forjadas] = enc.id_item;
        
        // Equipa o item no aventureiro correspondente
        aventureiros.getRegistro(enc.id_aventureiro).build.empilhar(enc.id_item); 
        forjadas++;
    }

    std::cout << "Z " << forjadas << "\n";
    
    if (forjadas > 0) {
        for (int i = 0; i < forjadas; i++) {
            std::cout << "encomenda_" << (i + 1) << " " << ids_aventureiros[i] << " " << ids_itens[i];
            if (i < forjadas - 1) std::cout << " ";
        }
        std::cout << "\n";
    }
}

// D <id_aventureiro> : Desequipa a última peça
void Forja::desequiparPecaAventureiro(int id_aventureiro) {
    Aventureiro& av = aventureiros.getRegistro(id_aventureiro);

    int id_item = av.build.desempilhar();
    if (id_item == -1) {
        std::cout << "D " << av.nome << " VAZIO\n";
    } else {
        std::string nome_item = catalogo.getNomeItem(id_item);
        std::cout << "D " << av.nome << " " << nome_item << "\n";
    }
}

// LI <id_item> : Lista todos os modificadores de um item
void Forja::consultarItem(int id_item) {
    std::string nome_item = catalogo.getNomeItem(id_item);
    
    int* ids_atributos = nullptr;
    int* valores = nullptr;
    int qtd_mod = catalogo.getAtributosDoItem(id_item, ids_atributos, valores);
    
    std::cout << "LI " << nome_item;
    if (qtd_mod == 0) { std::cout << " VAZIO\n"; } 
    else {
        // Imprime os atributos ordenados (ordenação por id já é garantida para lista de atributos)
        for (int i = 0; i < qtd_mod; i++) {
            std::cout << " atributo_" << (i+1) << " " << ids_atributos[i] << " " << valores[i];
        }
        std::cout << "\n";
    }
    
    delete[] ids_atributos;
    delete[] valores;
}

// LA <id_atributo> : Lista todos os itens com modificadores não-nulos para um determinado atributo
void Forja::consultarAtributo(int id_atributo) {
    std::string nome_atributo = catalogo.getNomeAtributo(id_atributo);
    
    int* ids_itens = nullptr;
    int* valores = nullptr;
    int qtd_itens = catalogo.getItensDoAtributo(id_atributo, ids_itens, valores);
    
    std::cout << "LA " << nome_atributo;
    if (qtd_itens == 0) { std::cout << " VAZIO\n"; }
    else {
        // Imprime os itens ordenados (ordenação por id já é garantida para lista de itens)
        for (int i = 0; i < qtd_itens; i++) {
            std::cout << " item_" << (i+1) << " " << ids_itens[i] << " " << valores[i];
        }
        std::cout << "\n";
    }
    
    delete[] ids_itens;
    delete[] valores;
}

// LH <id_aventureiro> : Lista a build atual do aventureiro
void Forja::consultarBuild(int id_aventureiro) {
    std::string nome_av = aventureiros.getRegistro(id_aventureiro).nome;
    
    int num_atributos = catalogo.getNumAtributos();
    int* vetor_build = new int[num_atributos](); // Inicializado com 0
    
    // Preenchimento do vetor_build lendo a pilha
    calcularVetorBuild(id_aventureiro, vetor_build);
    
    std::cout << "LH " << nome_av;
    
    // Imprime os atributos ordenados (ordenação por id já é garantida para lista de atributos/vetor_build)
    bool tem_mods = false;
    int contador = 1;
    for (int i = 0; i < num_atributos; i++) {
        if (vetor_build[i] != 0) {
            std::cout << " atributo_" << contador << " " << i << " " << vetor_build[i];
            tem_mods = true;
            contador++;
        }
    }
    
    if (!tem_mods) { std::cout << " VAZIO"; }
    std::cout << "\n";
    
    delete[] vetor_build;
}

// Q <id_aventureiro> <n> <m> ... : Sistema de recomendação global ponderado
// void Forja::consultarRecomendacao(int id_aventureiro, int n_recomendacoes, int m_metricas, 
//                                   const std::string* nomes_metricas, const double* pesos_metricas) const {
    
//     int N = catalogo.getNumItens();
//     double* pontuacoes_finais = new double[N](); // Inicia com 0.0

//     // O cálculo das métricas (Poder, Equilíbrio, Sinergia) dita uma ordenação global[cite: 2].
//     for (int i = 0; i < m_metricas; i++) {
//         // 1. Calcular pontuação matemática da métrica i para todos os itens
//         // 2. Ordenar globalmente os itens por esta pontuação (desempate por ID crescente)[cite: 2].
//         // 3. Atribuir aos itens o "N - posição" e multiplicar pelo pesos_metricas[i][cite: 2].
//         // 4. Acumular o resultado em pontuacoes_finais.
        
//         // (A chamada ao seu método interno de pontuação ocorre aqui: calcularPontuacaoItem(...) )
//     }

//     // Após combinadas, descarte itens que o aventureiro já possui equipados[cite: 2].
//     // Ordene o resultado final decrescentemente (desempate ID crescente)[cite: 2].
//     // ...
//     // (A chamada à função interna ordenarRecomendacoes(...) ocorre aqui).

//     // Saída restrita aos <n> maiores
//     // Formato com exatamente 6 casas decimais na pontuação[cite: 2].
//     std::cout << std::fixed << std::setprecision(6);
//     for (int rank = 0; rank < n_recomendacoes /* e rank < num_candidatos_restantes */; rank++) {
//         // Supondo acesso ordenado a um vetor candidatos[rank] que armazene id e pontuacao final
//         // std::cout << "Q " << (rank + 1) << " " << candidatos[rank].id << " " << candidatos[rank].pontuacao << "\n";
//     }
    
//     delete[] pontuacoes_finais;
// }

// LF <id_atributo> <valor_min> <valor_max> : Consulta de itens por faixa de valores (ponto extra)
void Forja::consultarItensNaFaixa(int id_atributo, int valor_min, int valor_max) {
    std::string nome_atributo = catalogo.getNomeAtributo(id_atributo);
    
    int* ids_itens = nullptr;
    int* valores = nullptr;
    int qtd_itens = catalogo.getItensNaFaixa(id_atributo, valor_min, valor_max, ids_itens, valores);

    std::cout << "LF " << nome_atributo;
    if (qtd_itens == 0) { std::cout << " VAZIO\n"; } 
    else {
        
        for (int i = 0; i < qtd_itens; i++) {
            std::cout << " item_" << (i+1) << " " << ids_itens[i] << " " << valores[i];
        }
        std::cout << "\n";
    }

    delete[] ids_itens;
    delete[] valores;
}