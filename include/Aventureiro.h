#ifndef AVENTUREIRO_H
#define AVENTUREIRO_H

#include <string>
#include "Pilha.h"

struct Aventureiro {
    int id;
    std::string nome;
    Pilha build;

    Aventureiro();
    Aventureiro(int id, const std::string& nome);
};

#endif