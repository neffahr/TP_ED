#include "Atributo.h"

Atributo::Atributo(int id, const std::string& nome) {
    this->id = id;
    this->nome = nome;
}

bool Atributo::operator<(const Atributo& outro) const {
    return this->id < outro.id;
}