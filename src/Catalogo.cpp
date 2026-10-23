#include "Catalogo.h"
#include <cmath>

Catalogo::Catalogo() {
    modo_atual = MODO_T;
    matriz_mods = new MatrizCOO(0, 0);
}

Catalogo::~Catalogo() { delete matriz_mods; }


// Metodos Privados
void Catalogo::converterParaMatrizL() {
    int l = itens.getTamanho();
    int c = atributos.getTamanho();
    MatrizEncadeada* nova = new MatrizEncadeada(l, c);

    if (matriz_mods != nullptr) {
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < c; j++) {
                int v = matriz_mods->Get(i, j);
                if (v != 0.0) {
                    nova->Set(i, j, v);
                }
            }
        }
    }

    delete matriz_mods;
    matriz_mods = nova;
}

void Catalogo::converterParaMatrizT() {
    int l = itens.getTamanho();
    int c = atributos.getTamanho();
    MatrizCOO* nova = new MatrizCOO(l, c);

    if (matriz_mods != nullptr) {
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < c; j++) {
                int v = matriz_mods->Get(i, j);
                if (v != 0.0) {
                    nova->Set(i, j, v);
                }
            }
        }
    }

    delete matriz_mods;
    matriz_mods = nova;
}


// Metodos Publicos
void Catalogo::definirModo(char modo) {
    if ((modo == 'L') && modo_atual != MODO_L) {
        converterParaMatrizL();
        modo_atual = MODO_L;
    } 
    else if ((modo == 'T') && modo_atual != MODO_T) {
        converterParaMatrizT();
        modo_atual = MODO_T;
    }
}

char Catalogo::getModo() const { return (modo_atual == MODO_L) ? 'L' : 'T'; }

std::string Catalogo::getNomeItem(int id_item) const {
    if (id_item < 0 || id_item >= itens.getTamanho()) return "";
    return itens.getRegistro(id_item).nome;
}

std::string Catalogo::getNomeAtributo(int id_atributo) const {
    if (id_atributo < 0 || id_atributo >= atributos.getTamanho()) return "";
    return atributos.getRegistro(id_atributo).nome;
}

int Catalogo::getNumItens() const {
    return itens.getTamanho();
}

int Catalogo::getNumAtributos() const {
    return atributos.getTamanho();
}

int Catalogo::registrarItem(const std::string& nome) {
    int id = itens.getTamanho();
    Item novo_item(id, nome);
    itens.insereFinal(novo_item);
    matriz_mods->redimencionarMatriz(itens.getTamanho(), atributos.getTamanho());
    return id;
}

int Catalogo::registrarAtributo(const std::string& nome) {
    int id = atributos.getTamanho();
    Atributo novo_atributo(id, nome);
    atributos.insereFinal(novo_atributo);
    matriz_mods->redimencionarMatriz(itens.getTamanho(), atributos.getTamanho());
    return id;
}

void Catalogo::definirModificador(int id_item, int id_atributo, int valor) {
    if (matriz_mods != nullptr) {
        matriz_mods->Set(id_item, id_atributo, valor);
    }
}

int Catalogo::obterModificador(int id_item, int id_atributo) const {
    if (matriz_mods == nullptr) return 0;
    return matriz_mods->Get(id_item, id_atributo);
}


// Consultas
int Catalogo::getAtributosDoItem(int id_item, int*& ids_atributos, int*& valores) {
    return matriz_mods->getLinha(id_item, ids_atributos, valores);
}

int Catalogo::getItensDoAtributo(int id_atributo, int*& ids_itens, int*& valores) {
    return matriz_mods->getColuna(id_atributo, ids_itens, valores);
}

// Métricas
int Catalogo::calcularPoder(int id_item) const {
    return matriz_mods->somarLinha(id_item);
}

double Catalogo::calcularEquilibrio(int id_item) const {
    int num_atributos = atributos.getTamanho();
    if (num_atributos == 0) return 1.0; 

    int* cols = nullptr;
    int* vals = nullptr;
    int qtd = matriz_mods->getLinha(id_item, cols, vals);

    double mu = (1.0 * calcularPoder(id_item)) / num_atributos;
    double soma_desvios = 0.0;

    for (int i = 0; i < qtd; i++) {
        double diff = vals[i] - mu;
        soma_desvios += (diff * diff);
    }

    // Somatório (0 - mu)^2 para as células nulas (num_atributos - qtd celulas)
    soma_desvios += (num_atributos - qtd) * (mu * mu);
    
    delete[] cols;
    delete[] vals;

    double sigma = std::sqrt(soma_desvios / num_atributos);
    return 1.0 / (1.0 + sigma);
}

double Catalogo::calcularSinergia(int id_item, const double* vetor_build, int soma_vetor_build) const {
    int num_atributos = atributos.getTamanho();
    if (num_atributos == 0) return 0.0;

    int* cols = nullptr;
    int* vals = nullptr;
    int qtd = matriz_mods->getLinha(id_item, cols, vals);

    int prod_interno = 0.0;
    int soma_vi = 0.0;

    for (int i = 0; i < qtd; i++) {
        int vi = vals[i];
        prod_interno += vi * vetor_build[cols[i]];
        soma_vi += vi * vi;
    }

    delete[] cols; delete[] vals;

    double denominador = std::sqrt(soma_vi) * std::sqrt(soma_vetor_build);
    if (denominador == 0.0) return 0.0; 
    return prod_interno / denominador;
}