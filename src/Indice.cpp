#include "Indice.h"
#include <stdexcept>

Indice::Indice(char modo) {
    if (modo == 'H') {
        this->modo = MODO_H;
        indice = new Hash();
    } else {
        this->modo = MODO_A;
        indice = new ArvoreAVL();
    }
}

Indice::~Indice() { delete indice; }


void Indice::definirModo(char modo) {
    if ((modo == 'A') && this->modo != MODO_A) {
        converterParaAVL();
        this->modo = MODO_A;
    } else if ((modo == 'H') && this->modo != MODO_H) {
        converterParaHash();
        this->modo = MODO_H;
    }
}

void Indice::converterParaAVL() {
    ArvoreAVL* nova_avl = new ArvoreAVL();

    if (indice != nullptr) {
        Lista<DadoIndice> registros;
        indice->exportarElementos(registros);

        for (int i = 0; i < registros.getTamanho(); i++) {
            nova_avl->insere(registros.getRegistro(i).poder, registros.getRegistro(i).id_cliente);
        }

        delete indice;
    }

    indice = nova_avl;
}

void Indice::converterParaHash() {
    Hash* nova_hash = new Hash();

    if (indice != nullptr) {
        Lista<DadoIndice> registros;
        indice->exportarElementos(registros);

        for (int i = 0; i < registros.getTamanho(); i++) {
            nova_hash->insere(registros.getRegistro(i).poder, registros.getRegistro(i).id_cliente);
        }

        delete indice;
    }

    indice = nova_hash;
}


int Indice::registrarAtributo(const std::string& nome) {
    int id = atributos.getTamanho();
    Atributo novo_atributo(id, nome);
    atributos.insereFinal(novo_atributo);
    return id;
}


void Indice::insere(int poder, int id_cliente) {
    if (indice != nullptr) {
        indice->insere(poder, id_cliente);
    }
}

void Indice::remove(int poder, int id_cliente) {
    if (indice != nullptr) {
        indice->remove(poder, id_cliente);
    }
}

void Indice::buscaPontual(int poder, Lista<int>& resultado) const {
    if (indice != nullptr) {
        indice->buscaPontual(poder, resultado);
    }
}

void Indice::buscaFaixa(int min, int max, Lista<DadoIndice>& resultado) const {
    if (indice != nullptr) {
        indice->buscaFaixa(min, max, resultado);
    }
}


char Indice::getModo() const { 
    return (this->modo == MODO_A) ? 'A' : 'H'; 
}

int Indice::getNumAtributos() const { 
    return atributos.getTamanho(); 
}

std::string Indice::getNomeAtributo(int id_atributo) const { 
    return atributos.getRegistro(id_atributo).nome; 
}

int Indice::getTamanho() const { 
    return (indice != nullptr) ? indice->getTamanho() : 0; 
}

bool Indice::vazia() const {
    return (indice != nullptr) ? indice->vazia() : true;
}