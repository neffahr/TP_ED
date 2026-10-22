#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <string>

struct Atributo {
    int id;
    std::string nome;

    Atributo() : id(-1), nome("") {}
    Atributo(int id, const std::string& nome);
};

#endif