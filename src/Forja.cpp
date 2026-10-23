#include "Forja.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Forja::Forja() {}
Forja::~Forja() {}

void Forja::alterarModo(char modo) {
    catalogo.definirModo(modo); 
    std::cout << "E " << catalogo.getModo() << "\n";
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
    while (!fila_encomendas.vazia() && forjadas < k) {
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
    double* vetor_build = new double[num_atributos](); // Inicializado com 0
    
    // Preenchimento do vetor_build lendo a pilha
    calcularVetorBuild(id_aventureiro, vetor_build);
    
    std::cout << "LH " << nome_av;
    
    // Imprime os atributos ordenados (ordenação por id já é garantida para lista de atributos/vetor_build)
    bool tem_mods = false;
    int contador = 1;
    for (int i = 0; i < num_atributos; i++) {
        int valor = vetor_build[i];
        if (valor != 0) {
            std::cout << " atributo_" << contador << " " << i << " " << valor;
            tem_mods = true;
            contador++;
        }
    }
    
    if (!tem_mods) { std::cout << " VAZIO"; }
    std::cout << "\n";
    
    delete[] vetor_build;
}

void Forja::calcularVetorBuild(int id_aventureiro, double* vetor_build) {
    int num_atributos = catalogo.getNumAtributos();
    if (num_atributos == 0) return;

    // Zera vetor
    for (int a = 0; a < num_atributos; a++) {
        vetor_build[a] = 0.0;
    }

    // Obtém o aventureiro e build
    const Aventureiro& av = aventureiros.getRegistro(id_aventureiro);
    Pilha pilha_aux = av.build;

    // Passaa por cada item na build e acumula modificadores não-nulos
    while (!pilha_aux.vazia()) {
        int id_item = pilha_aux.desempilhar();

        int* ids_atributos = nullptr;
        int* valores = nullptr;

        // Recupera apenas os atributos não-nulos da linha do item no catálogo
        int qtd = catalogo.getAtributosDoItem(id_item, ids_atributos, valores);

        for (int c = 0; c < qtd; c++) {
            vetor_build[ids_atributos[c]] += valores[c];
        }

        delete[] ids_atributos;
        delete[] valores;
    }
}

void Forja::ordenar(int* ids_itens, double* valores, int n) {
    for (int i = 1; i < n; i++) {
        int key_id = ids_itens[i];
        double key_val = valores[i];
        int j = i - 1;

        while (j >= 0) {
            // Arredonda para 6 casa decimais
            double v_atual = std::round(valores[j] * 1000000.0) / 1000000.0;
            double v_chave = std::round(key_val * 1000000.0) / 1000000.0;

            bool precisa_trocar = false;

            if (v_atual < v_chave) {
                precisa_trocar = true;
            } else if (v_atual == v_chave && ids_itens[j] > key_id) {
                precisa_trocar = true;
            }

            if (!precisa_trocar) break;

            ids_itens[j + 1] = ids_itens[j];
            valores[j + 1] = valores[j];
            j--;
        }
        ids_itens[j + 1] = key_id;
        valores[j + 1] = key_val;
    }
}

// Q <id_aventureiro> <n> <m> ... : Sistema de recomendação global ponderado
void Forja::consultarRecomendacao(int id_aventureiro, int n, int m, const std::string* nomes_metricas, const double* pesos_metricas) {
    int num_itens = catalogo.getNumItens();
    int num_atributos = catalogo.getNumAtributos();

    if (num_itens == 0) return;

    // Monta vetor de build e calcula soma dos quadrados do vetor para sinergia
    double* bh = new double[num_atributos];
    calcularVetorBuild(id_aventureiro, bh);

    double soma_quadrados_build = 0.0;
    for (int a = 0; a < num_atributos; a++) {
        soma_quadrados_build += bh[a] * bh[a];
    }

    // Avalia cada métrica informada e calcula pontuações para cada item
    double* pontuacoes_itens = new double[num_itens]();
    for (int i = 0; i < m; i++) {
        std::string metrica = nomes_metricas[i];
        double peso = pesos_metricas[i];

        int* ids_itens = new int[num_itens];
        double* valores = new double[num_itens];

        // Calcula métrica para todos os itens do catalogo
        for (int i = 0; i < num_itens; i++) {
            ids_itens[i] = i;
            if (metrica == "PODER") {
                valores[i] = catalogo.calcularPoder(i);
            } else if (metrica == "EQUILIBRIO") {
                valores[i] = catalogo.calcularEquilibrio(i);
            } else if (metrica == "SINERGIA") {
                valores[i] = catalogo.calcularSinergia(i, bh, soma_quadrados_build);
            }
        }

        // Ordena itens pelo valor da métrica
        ordenar(ids_itens, valores, num_itens);

        // Calcula pontuação
        for (int pos = 0; pos < num_itens; pos++) {
            int id_item = ids_itens[pos];
            double pontos = (num_itens - pos) * peso;
            pontuacoes_itens[id_item] += pontos;
        }

        delete[] ids_itens;
        delete[] valores;
    }

    // Descarta dos itens que o aventureiro já possui equipados na sua build atual
    bool* equipado = new bool[num_itens]();
    const Aventureiro& av = aventureiros.getRegistro(id_aventureiro);
    Pilha pilha_aux = av.build;
    while (!pilha_aux.vazia()) {
        equipado[pilha_aux.desempilhar()] = true;
    }

    int num_candidatos = 0;
    for (int i = 0; i < num_itens; i++) {
        if (!equipado[i]) num_candidatos++;
    }

    // Se nenhum item estiver disponível para recomendação, nao produz saída
    if (num_candidatos == 0) {
        delete[] bh;
        delete[] pontuacoes_itens;
        delete[] equipado;
        return;
    }

    // Coleta os itens não equipados e ordena pelo ranking final de pontuação
    int* ids_candidatos = new int[num_candidatos];
    double* pontuacoes_candidatos = new double[num_candidatos];

    int idx = 0;
    for (int i = 0; i < num_itens; i++) {
        if (!equipado[i]) {
            ids_candidatos[idx] = i;
            pontuacoes_candidatos[idx] = pontuacoes_itens[i];
            idx++;
        }
    }

    ordenar(ids_candidatos, pontuacoes_candidatos, num_candidatos);

    // Imprime os top n recomendados
    int num_recomendacoes = std::min(n, num_candidatos);
    for (int i = 0; i < num_recomendacoes; i++) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Q " << (i + 1) << " " << ids_candidatos[i] << " " << pontuacoes_candidatos[i] << "\n";
    }

    // Desalocação de memória
    delete[] bh;
    delete[] pontuacoes_itens;
    delete[] equipado;
    delete[] ids_candidatos;
    delete[] pontuacoes_candidatos;
    
}