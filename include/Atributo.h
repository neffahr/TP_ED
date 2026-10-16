#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <string>

struct Atributo {
    int id;
    std::string nome;

    Atributo();
    Atributo(int id, const std::string& nome);
};

#endif