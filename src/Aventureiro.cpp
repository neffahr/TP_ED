#include "Aventureiro.h"

Aventureiro::Aventureiro() : id(-1), nome("") {}

Aventureiro::Aventureiro(int id, const std::string& nome) {
    this->id = id;
    this->nome = nome;
}