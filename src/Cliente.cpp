#include "Cliente.h"

Cliente::Cliente() : id(-1), nome(""), poder(0), qtd_atributos(0), build(nullptr) {}

Cliente::Cliente(int id, const std::string& nome, const int* build, int qtd_atributos) {
    this->id = id;
    this->nome = nome;
    this->qtd_atributos = qtd_atributos;
    this->poder = 0;

    if (qtd_atributos > 0 && build != nullptr) {
        this->build = new int[qtd_atributos];

        for (int i = 0; i < qtd_atributos; i++) {
            this->build[i] = build[i];
            this->poder += build[i];
        }

    } else this->build = nullptr;
}

Cliente::~Cliente() { delete[] build; }

Cliente::Cliente(const Cliente& copiado) {
    this->id = copiado.id;
    this->nome = copiado.nome;
    this->poder = copiado.poder;
    this->qtd_atributos = copiado.qtd_atributos;

    if (copiado.qtd_atributos > 0 && copiado.build != nullptr) {
        this->build = new int[copiado.qtd_atributos];

        for (int a = 0; a < copiado.qtd_atributos; a++) {
            this->build[a] = copiado.build[a];
        }

    } else this->build = nullptr;
}

Cliente& Cliente::operator=(const Cliente& copiado) {
    if (this != &copiado) {
        delete[] this->build;

        this->id = copiado.id;
        this->nome = copiado.nome;
        this->poder = copiado.poder;
        this->qtd_atributos = copiado.qtd_atributos;

        if (copiado.qtd_atributos > 0 && copiado.build != nullptr) {
            this->build = new int[copiado.qtd_atributos];

            for (int a = 0; a < copiado.qtd_atributos; a++) {
                this->build[a] = copiado.build[a];
            }
            
        } else this->build = nullptr;
    }
    return *this;
}